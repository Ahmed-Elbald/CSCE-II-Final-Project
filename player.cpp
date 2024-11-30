#include "player.h"
#include "game.h"

Player::Player() {

    // Initialize player
    init();

}

// Logic
void Player::init() {

    // Loading audio files
    loadAudioFiles();

    // Loading sprite sheets
    loadSpriteSheetImages();

    // Set sprite sheet properties
    setProperties(
        SM.settings->value("player/spriteFrameWidth").toInt(),
        SM.settings->value("player/spriteFrameHeight").toInt(),
        SM.settings->value("player/spriteContentOffsetX").toInt(),
        SM.settings->value("player/spriteContentOffsetY").toInt(),
        SM.settings->value("player/spriteContentWidth").toInt(),
        SM.settings->value("player/spriteContentHeight").toInt()
    );

    // Walk timer
    walkTimer = new QTimer(this);
    connect(walkTimer, &QTimer::timeout, this, &Player::walk);

    // Jump timer
    jumpTimer = new QTimer(this);
    fallTimer = new QTimer(this);

    // Collision Timer
    collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &Player::handleCollision);

    // Shield
    shield = new ShieldEffect(this);
    shield->setOpacity(0);

}

void Player::startLevel() {


    // // Start timers
    collisionTimer->start(collisionTimerInterval);

    // // Add the shield if not there
    if (!scene()->items().contains(shield))
        scene()->addItem(shield);

    // // enable shield after 1 seconds (Debugging)
    // QTimer::singleShot(1000, this, &Player::enableShield);


    // Set the player's initial position and sprite
    setSpritePixmap(spriteSheetImages[dominantAction]);

    qDebug() << "Sprite pixmap set" << pixmap().width() << pixmap().height();
    qDebug() << spriteSheetImages[dominantAction].width() << spriteSheetImages[dominantAction].height();
    setPos(game->getStartOffset(), game->getGroundLevel() - boundingRect().height());

    // Shield
    shield->init();

    // Activate Player
    activate();

}

void Player::activate() {
    // Connect the key press event
    connect(this, &Player::keyPressEvent, this, &Player::keyPressEvent);

    // Update the sprite sheet
    setCurrentSprite();

    // Show the player
    show();
}

void Player::deactivate() {

    // Stop current actions
    stopWalking();

    // Disconnect the key press event
    disconnect(this, &Player::keyPressEvent, nullptr, nullptr);

    // Remove all pressed keys
    keysPressed.clear();

    // Set the initial state
    dominantAction = IDLE;

    // Deactivate shield
    disableShield();
}

// Walking
void Player::handleWalking() {

    isWalking = true;
    // Play Walking sound
    walkSound->play();
    // Start timer to handle horizontal movement
    walkTimer->start(walkTimerInterval);

}

void Player::stopWalking() {
    // Stop walking sound
    walkSound->stop();
    // Stop the horizontal movement timer
    walkTimer->stop();
    // Remove the walking action
    // currentActions.remove(WALK);
    isWalking = false;
    // Update the sprite sheet
    setCurrentSprite();
}


void Player::walk() {

    // Do not move if the player is jumping
    if (isJumping || isDying) {
        stopWalking();
        return;
    }

    // Fall if the player is not on the ground
    int shift = isRunning ? runShift : walkShift;
    if (!isJumping && !isFalling && qAbs(game->getGroundLevel() - boundingRect().height() - y()) > 2 && (validateNewPosition(0, 3) == nullptr || validateNewPosition(5, 3) == nullptr || validateNewPosition(-5, 3) == nullptr)) {
        handleFalling((shift - 2) * direction);
        stopWalking();
        return;
    }


    // If the player wants to walk to the left
    if (keysPressed.contains(Qt::Key_Left)) {
        // Make the displacement in negative direction
        shift *= -1;

        // Change the direction of the player if needed
        changeDirection(LEFT);
    } else if (keysPressed.contains(Qt::Key_Right))
        changeDirection(RIGHT);

    // Move the player if the new position is valid //

    // Get the colliding item (if it exists)
    QGraphicsItem *collidingItem = validateNewPosition(shift, 0);

    // If it is a block
    if (collidingItem != nullptr && collidingItem->type() == BlockType) {
        // Stop at the most valid place
        setPos(x() + findBestPosition(shift, 0, 0), y());

        // Emit the player position changed signal
        emit playerPositionChanged();

        // Stop walking
        stopWalking();
    }
    else { // Otherwise, move the player
        setPos(x() + shift, y());
        emit playerPositionChanged();
    }

}


// Jumping
void Player::handleJumping() {

    // Do not jump if the player is already jumping
    if (isJumping)
        return;

    // Change state
    isJumping = true;

    // Play jump sound
    jumpSound->play();

    // Set the initial vertical velocity
    verticalVelocity = jumpVelocity;

    // Adjust player direction
    if (keysPressed.contains(Qt::Key_Left))
        changeDirection(LEFT);
    else if (keysPressed.contains(Qt::Key_Right))
        changeDirection(RIGHT);

    // Shift the player horizontally if needed
    int xShift = 0;
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        xShift = direction * (isRunning ? runShift : walkShift);

    // Disconnect timer
    jumpTimer->disconnect();

    // Set up timer
    jumpTimer->connect(jumpTimer, &QTimer::timeout, this, [=](){
        jump(xShift);
    });

    // Start jumping
    jumpTimer->start(jumpTimerInterval);
}

void Player::jump(int xShift) {

    // Update vertical position
    verticalVelocity += gravity;
    setY(y() + verticalVelocity);

    // If the player's velocity is turning posititve
    if (verticalVelocity >= 0) {

        // Stop the jump
        jumpTimer->stop();

        // Fall
        handleFalling(xShift);

        // Go out
        return;
    }

    // Get the colliding item for the vertical shift (if it exists)
    QGraphicsItem *collidingItem = validateNewPosition(xShift, verticalVelocity);

    // If no collision
    if (collidingItem == nullptr)
        setY(y() + verticalVelocity);

    // Otherwise
    else {

        // Go up to the most valid place
        setY(y() + findBestPosition(xShift, verticalVelocity, 0));

        // Fall
        handleFalling();

        // Go out
        return;
    }

    // Get the colliding item for the horizontal shift (if it exists)
    collidingItem = validateNewPosition(xShift, 0);

    // Shift if no collision
    if (xShift != 0 && collidingItem == nullptr) {
        setX(x() + xShift);
        emit playerPositionChanged();
    }

    // Increase the vertical velocity
    verticalVelocity += gravity;
}


// Falling
void Player::handleFalling(int xShift) {

    // Do not fall if the player is already falling
    if (isFalling)
        return;

    // Set the initial vertical velocity
    verticalVelocity = 0;

    // Change state
    isFalling = true;

    // Disconnect timer
    fallTimer->disconnect();

    // Set up timer
    fallTimer->connect(fallTimer, &QTimer::timeout, this, [=](){
        fall(xShift);
    });

    // Start timer
    fallTimer->start(fallTimerInterval);
}

void Player::fall(int xShift) {

    // Check if the player is on or passed the ground
    if (y() >= game->getGroundLevel() - boundingRect().height()) {
        setY(game->getGroundLevel() - boundingRect().height());
        stopFalling();
        return;
    }

    // Get the colliding item for the vertical shift (if it exists)
    QGraphicsItem *collidingItem = validateNewPosition(xShift, verticalVelocity);

    // If it is colliding with a blcok
    if (collidingItem != nullptr && collidingItem->type() == BlockType) {

        // If the player's foot is above the block, land on it
        if (y() + boundingRect().height() - verticalVelocity <= collidingItem->y()) {
            setY(collidingItem->y() - boundingRect().height());
            stopFalling();
            return;
        }

        // Otherwise, move the player by the current vertical velocity
        else {
            setY(y() + verticalVelocity);
        }

    }
    // Otherwise, do the noraml falling
    else
        setY(y() + verticalVelocity);

    // Move horizontally if no collision
    if (xShift != 0 && validateNewPosition(xShift) == nullptr) {
        setX(x() + xShift);
        emit playerPositionChanged();
    }

    // Update the vertical velocity
    verticalVelocity += gravity;
}


void Player::stopFalling() {

    // Remove the fall action
    isFalling = false;
    isJumping = false;

    // Stop the fall timer
    fallTimer->stop();

    // If the player was moving before falling, continue moving (if needed)
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        handleWalking();

    // Update the sprite sheet
    setCurrentSprite();
}

// Dying
void Player::handleDying() {

    // Avoid conflicting dies
    if (isDying)
        return;

    // Change state
    isDying = true;

    // One time die
    die();
}

void Player::die() {

    // Play dying sound
    dieSound->play();

    // Stop the dying after 225ms
    QTimer::singleShot(225, this, &Player::stopDying);

}

void Player::stopDying() {

    // Hide player
    hide();

    // Restart level after 1000 second
    QTimer::singleShot(1000, this, &Player::moveToStartOver);

    // Update the sprite sheet
    setCurrentSprite();

}

// Collision
void Player::handleCollision() {

    // For all colliding items
    for(QGraphicsItem * item : collidingItems()) {

        // If the item is the shield or the player, ignore it
        if (item == shield || item == this) continue;

        // If the item is a trap
        if (item->type() == TrapType)
            handleDangerCollision(item);
        else if (item->type() == CoinType)
            handleCoinCollision(item);
        // else if (item->type() == ShieldType)
        //     handleShieldCollision(item);
        // else if (item->type() == PowerUpType)
        //     handlePowerUpCollision(item);
    }
}

void Player::handleDangerCollision(QGraphicsItem* item) {

    // If the player has a shield and the item is a trap
    if (hasShield && item->type() == TrapType) {
        // Remove item from the scene and delete it
        game->scene->removeItem(item);
        delete item;

        // Play destroy sound
        destroySound->play();
    }
    // Otherwise, die
    else
        handleDying();
}

void Player::handleCoinCollision(QGraphicsItem* item) {

    // Remove item from the scene and delete it
    game->scene->removeItem(item);
    delete item;

    // Play coin sound
    coinSound->play();

    // Increase the player's score
    game->state->incrementCoins();
    game->score->increase();
}

// Shields
void Player::enableShield() {
    shield->setOpacity(1);
    shieldActiviationSound->play();
    wooHooSound->play();
    hasShield = true;
}

void Player::disableShield() {
    shield->setOpacity(0);
    hasShield = false;
}

// Setters
void Player::setDominantAction(PlayerActions action) {
    dominantAction = action;
}

// Helpers
void Player::loadAudioFiles() {
    jumpSound = new Sound(SM.settings->value("audio/jumpSound").toString());
    walkSound = new Sound(SM.settings->value("audio/walkSound").toString(), 1, QMediaPlayer::Infinite);
    dieSound = new Sound(SM.settings->value("audio/dieSound").toString());
    shieldActiviationSound = new Sound(SM.settings->value("audio/shieldActivationSound").toString());
    coinSound = new Sound(SM.settings->value("audio/coinSound").toString());
    destroySound = new Sound(SM.settings->value("audio/destroySound").toString());
    wooHooSound = new Sound(SM.settings->value("audio/wooHooSound").toString());
}

void Player::loadSpriteSheetImages() {
    for(int i = 0; i < PLAYER_ACTIONS.size(); i++) {
        QString filename = PLAYER_ACTIONS[i];
        filename[0] = filename[0].toUpper();
        QString path = QString(":/Assets/images/Fighter/%1.png").arg(filename);
        QPixmap pixmap(path);
        spriteSheetImages.push_back(pixmap);
    }
}

void Player::setCurrentSprite() {
    PlayerActions newDominantAction;
    if (isDying)
        newDominantAction = DIE;
    else if (isJumping)
        newDominantAction = JUMP;
    else if (isWalking)
        newDominantAction = isRunning ? RUN : WALK;
    else
        newDominantAction = IDLE;

    if (newDominantAction != dominantAction)
        setSpritePixmap(spriteSheetImages[newDominantAction], newDominantAction == JUMP ? oneTime : repeating);

    dominantAction = newDominantAction;
}

void Player::changeDirection(PlayerDirections newDirection) {
    // If the player is already facing the new direction, do nothing
    if (direction == newDirection)
        return;

    // Change the direction of the player
    setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
    direction = newDirection;
}

void Player::hide() {
    setOpacity(0);
}

void Player::show() {
    setOpacity(1);
}

QGraphicsItem* Player::validateNewPosition(double dx, double dy) {
    int newXPosition = x() + dx, newYPosition = y() + dy;

    // Scene Boundries
    if (newXPosition - startOffset < 0)
        return this;

    // Check for collisions
    QRectF newRect(newXPosition, newYPosition, boundingRect().width(), boundingRect().height());
    QList<QGraphicsItem*> collidingItems = game->scene->items(newRect);
    for(QGraphicsItem * item : collidingItems) {
        if (item == this)
            continue;
        if (item->type() == TrapType || item->type() == BlockType)
            return item;
    }

    return nullptr;
}

void Player::moveToStartOver() {

    // New Timer
    QTimer *timer = new QTimer(this);

    // Connect
    connect(timer, &QTimer::timeout, this, [=](){

        // Move the player to the start position
        if (x() > game->getStartOffset()) {
            setX(x() - 15);
            emit playerPositionChanged();
        }

        // If the player is at or passed the start position
        else {

            // Move the player to the start position
            setPos(game->getStartOffset(), game->getGroundLevel() - boundingRect().height());

            // Stop timer and delete it
            timer->stop();
            timer->disconnect();
            delete timer;

            // Show the player
            show();
            isDying = false;

            // Update the sprite sheet
            setCurrentSprite();
        }
    });


    // Start timer
    timer->start(16);
}

double Player::findBestPosition(double dx, double dy, double l) {
    double r = dy;
    int loop = 30;
    while(loop--) {
        double mid = (l + r) / 2;
        if (validateNewPosition(dx, mid) == nullptr) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

// Slots
void Player::keyPressEvent(QKeyEvent *event) {

    // Avoid auto repeat key press
    if (event->isAutoRepeat())
        return;

    // Avoid multiple key presses
    if (keysPressed.contains(event->key()))
        return;

    // Add the key to the pressed keys set
    keysPressed.insert(event->key());

    // Handle the key press
    if (event->key() == Qt::Key_Shift)
        isRunning = true;
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        // Handle walking
        handleWalking();
    else if (event->key() == Qt::Key_Space)
        // Handle the jump
        handleJumping();

    // Update the sprite sheet
    setCurrentSprite();
}

void Player::keyReleaseEvent(QKeyEvent *event) {

    // Avoid auto repeat key release
    if (event->isAutoRepeat())
        return;

    // Avoid multiple removes
    if (!keysPressed.contains(event->key()))
        return;

    // Remove the key from the pressed keys set
    keysPressed.remove(event->key());

    // Handle the key release
    if ((event->key() == Qt::Key_Left && !keysPressed.contains(Qt::Key_Right))
        || (event->key() == Qt::Key_Right && !keysPressed.contains(Qt::Key_Left)))
        stopWalking();
    else if (event->key() == Qt::Key_Shift)
        isRunning = false;

    // Update the sprite sheet
    setCurrentSprite();
}

// void Player::focusOutEvent(QFocusEvent *event) {
//     // Give the focus back to the player
//     Q_UNUSED(event);
//     setFocus();
// }


// Destructor
Player::~Player() {
    delete jumpSound;
    delete walkSound;
    delete dieSound;
    delete jumpTimer;
    delete walkTimer;
    delete fallTimer;
    delete collisionTimer;
    delete shield;
}
