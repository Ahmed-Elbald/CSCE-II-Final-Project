#include "game.h"
#include "block.h"
#include "lifedisplay.h"
#include "qapplication.h"
#include "soundplayer.h"
#include "trap.h"
#include "settingsmanager.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QResizeEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QBrush>
#include <QGraphicsView>
#include "coin.h"
#include <QGraphicsProxyWidget>
#include "enemy.h"
#include "healthpotion.h"
#include "soundplayer.h"


Game::Game() {

    // Initialize game
    init();

}


// Logic
void Game::init() {

    // Initialize sound player
    SP.init();

    // Play starting menu sound
    SP.startingMenuMusic->play();

    // Initialize game starting menu
    startingMenu = new StartingMenu();
    startingMenu->show();

    connect(startingMenu, &StartingMenu::startGameSignal, this, &Game::startCurrentLevel);
    connect(startingMenu, &StartingMenu::exitGameSignal, this, &Game::close);


    // Initialize state and level
    state = new State();

    // Initialize Scene
    scene = new QGraphicsScene();
    setScene(scene);

    // View width and height
    setFixedSize(SM.settings->value("window/width").toInt(), SM.settings->value("window/height").toInt());

    // Ensuring view can receive focus
    setFocusPolicy(Qt::StrongFocus);

    // Initialize Player
    player = new Player();
    scene->addItem(player);
    connect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);

    // End flag
    endFlag = new QGraphicsPixmapItem(QPixmap(SM.settings->value("scene/endFlag").toString()).scaled(75, 115));
    scene->addItem(endFlag);

    // create score

    score = new Score();
    scene->addItem(score);


    // Coins displayer
    coinsDisplayer = new CoinsDisplay();
    coinsDisplayer->setPos(
        SM.settings->value("window/coinsDisplayerXOffset").toInt(),
        SM.settings->value("window/coinsDisplayerYOffset").toInt()
        );
    scene->addItem(coinsDisplayer);

    // Life displayer
    lifeDisplay = new LifeDisplay(state);
    lifeDisplayer = scene->addWidget(lifeDisplay);

    // emit state->stateChanged();

    // Connect state change signal
    connect(state, &State::stateChanged, this, &Game::handleStateChange);

}


void Game::startCurrentLevel() {



    // Initialize level
    if (level != nullptr)
        delete level;

    this->setWindowTitle("RUN - Level " + QString::number(state->getLevel()));

    if (startingMenu != nullptr)
        startingMenu->close();

    // Adjusting Sound
    SP.startingMenuMusic->stop();
    QTimer::singleShot(1000, [=](){
        SP.bgMusic->play();
    });

    this->show();

    level = new Level(LEVELS[state->getLevel() - 1]);

    // Scene width, height, and background
    scene->setSceneRect(0, 0, level->getSceneWidth(), level->getSceneHeight());
    scene->setBackgroundBrush(QBrush(QPixmap(level->getBackgroundPath()).scaled(width(), height())));

    // Player and Scene
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->startLevel();


    // Move with player
    // Disconnect from the playerPositionChanged signal and connect again
    disconnect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);
    connect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);
    moveWithPlayer();

    // Set scroll policies to hide scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    clearMap();

    // Create obstacles
    createMap();

    // Play Background Music
    SP.bgMusic->play();

    // End flag position
    endFlag->setPos(scene->width() - getEndOffset(), getGroundLevel() - endFlag->boundingRect().height());

}


void Game::handleNewLevel() {

    // Stop player movement
    player->clearFocus();
    player->setFlag(QGraphicsItem::ItemIsFocusable, false);

    // Give Player IDLE state
    player->deactivate();

    // Stop the background music
    SP.bgMusic->stop();

    // Play the win sound
    SP.levelWinSound->play();

    // play "victory" sound after 500 ms
    QTimer::singleShot(1000, [=](){
        SP.victorySound->play();
        if (state->getLevel() != LEVELS.size()) {
            state->setLevel(state->getLevel() + 1);
            startCurrentLevel();
        } else
            state->setIsGameOver(true);
    });

}

void Game::close() {
    QApplication::quit();
}


// Slots
void Game::handlePlayerMovement() {

    if (player->x() >= scene->width() - getEndOffset() - player->boundingRect().width()) {
        // Handle the transition to a new level
        handleNewLevel();
        // Disconnect player position change signal
        disconnect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);
        return;
    }

    // Move view with the player
    moveWithPlayer();

    // Move displayers with the player
    mapDisplayersToScene();
}

void Game::KeyPressEvent(QKeyEvent *event)
{
    // Prevent moving the view if it has focus
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left) {
        event->accept();
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

void Game::handleStateChange() {
    coinsDisplayer->set(state->getCoins());
}

// Helpers
void Game::moveWithPlayer() {

    // Center the view on the player with boundaries
    qreal x = qBound(viewport()->width() / 2.0, player->x(), scene->width() - viewport()->width() / 2.0);
    centerOn(x, viewport()->height() / 2.0);

}

void Game::clearMap() {
    for ( auto element : scene->items()){
        for ( auto type : mapTypes){
            if ( !element ){
                continue;
            }
            if ( element->type() == type ){
                scene->removeItem(element);
            }
        }
    }
    elements.clear();
}



void Game::createMap() {

    int blockStartX = SM.settings->value("blocks/startX").toInt();
    int blockHeight = SM.settings->value("blocks/height").toInt();
    int blockDistanceFromGround = SM.settings->value("blocks/distanceFromGround").toInt();
    QString coinPath = SM.settings->value("coin/spriteSheet/1").toString();
    QString spike1Path = SM.settings->value("spikes/1").toString();
    QString block1Path= SM.settings->value("blocks/1").toString();
    QString block2Path = SM.settings->value("blocks/2").toString();
    int blockWidth = SM.settings->value("blocks/width").toInt();
    int coinRatio = SM.settings->value("ratios/coin").toInt();
    int healthPotionRatio = SM.settings->value("ratios/healthPotion").toInt();
    QString healthPotionPath = SM.settings->value("potion/health/path").toString();
    int pickUpHeight = SM.settings->value("pickUps/height").toInt();
    int potionScale = SM.settings->value("potion/health/scale").toInt();
    int coinScale = SM.settings->value("coin/scale").toInt();
    int enemyScale = SM.settings->value("enemy/scale").toInt();
    int blockScale = SM.settings->value("blocks/scale").toInt();
    int blockCollectionNumber = SM.settings->value("blocks/collectionNumber").toInt();
    int blockCollectionDistance = SM.settings->value("blocks/collectionDistance").toInt();
    int enemyHeight = SM.settings->value("enemy/spriteFrameHeight").toInt();
    int spikeScale = SM.settings->value("spikes/scale").toInt();
    int enemyRatio = SM.settings->value("ratios/enemy").toInt();
    int numberOfCollections = SM.settings->value("blocks/numberOfCollections").toInt();


    for ( int i = 0 ; i < numberOfCollections ; i++){
        for ( int  j = 0 ; j < blockCollectionNumber ; j++ ){
            qreal X = (blockStartX + blockWidth*j) + (blockCollectionNumber*blockWidth + blockCollectionDistance)*(i) ;
            qreal Y = this->getGroundLevel() - blockDistanceFromGround;
            auto *block = new Block( X , Y  ,   block1Path , blockScale );
            addElement(block);
            // Create potions and coins randomly
            int randomCoin = RandomNumber(0, coinRatio);
            int randomPotion = RandomNumber(0, healthPotionRatio);
            if (!randomCoin){
                Coin *coin = new Coin(X, Y  -pickUpHeight , coinScale , 1 , coinPath);
                addElement(coin);
            }
            if (!randomPotion){
                auto *potion = new HealthPotion(X , Y - pickUpHeight , potionScale , healthPotionPath);
                addElement(potion);
            }

            // Create Enemy Randomly
            int randomEnemy = RandomNumber(0, enemyRatio);
            if (!randomEnemy){
                auto *enemy = new Enemy(X, Y - blockHeight - enemyHeight, enemyScale);
                addElement(enemy);
            }
            // Create Spike
            if ( j == blockCollectionNumber -1 ){
                auto *trap = new Trap(X + blockWidth, getGroundLevel() - 20 , spike1Path , spikeScale );
                addElement(trap);
            }
        }
    }
}

void Game::mapDisplayersToScene() {
    QPointF coinsTopLeft = mapToScene(
        SM.settings->value("window/coinsDisplayerXOffset").toInt(),
        SM.settings->value("window/coinsDisplayerYOffset").toInt()
        );
    coinsDisplayer->setPos(coinsTopLeft.x(), coinsTopLeft.y());

    QPointF scorePos = mapToScene(viewport()->width() / 2.0 - score->boundingRect().width() / 2.0,  // center horrizontally to the screen
                                  10);
    score->setPos(scorePos.x(), scorePos.y());

    QPointF lifeTopLeft = mapToScene(
        SM.settings->value("window/lifeDisplayerXOffset").toInt(),
        SM.settings->value("window/lifeDisplayerYOffset").toInt()
        );
    lifeDisplayer->setPos(lifeTopLeft.x(), lifeTopLeft.y());
}


// Getters
float Game::getGroundLevel() {
    return level->getGroundLevel();
}

int Game::getStartOffset() {
    return level->getStartOffset();
}

int Game::getEndOffset() {
    return level->getEndOffset();
}

int Game::getSceneWidth() {
    return level->getSceneWidth();
}

int Game::getSceneHeight() {
    return level->getSceneHeight();
}

void Game::addElement(QGraphicsPixmapItem *element) {

    int endOffset = SM.settings->value("levelEndOffset").toInt();

    if ( element->x() > scene->width() -  endOffset || element->x() < 0 )
    {
        return;
    }

    elements.push_back(element);
    scene->addItem(element);
}


// Destructor
Game::~Game() {
    delete scene;
    delete player;
    delete state;
    delete endFlag;
    delete coinsDisplayer;
    delete lifeDisplayer;
    delete startingMenu;
    for (auto element : elements)
        delete element;

}
