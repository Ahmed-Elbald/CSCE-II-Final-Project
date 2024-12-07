#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "coinsdisplay.h"
#include "level.h"
#include "lifedisplay.h"
#include "player.h"
#include <QMediaPlayer>
#include "State.h"
#include "startingmenu.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:

    // UI
    QGraphicsPixmapItem *endFlag = nullptr;
    StartingMenu *startingMenu = nullptr;

public:
    // TODO: Make them private and modify that everywhere
    QVector<QGraphicsPixmapItem*> elements;
    QVector<CustomTypes> mapTypes = {
        BlockType,
        TrapType,
        CoinType,
        EnemyType,
        HealthPotionType
    };
    State *state = nullptr;
    Level *level = nullptr;
    CoinsDisplay *coinsDisplayer = nullptr; // TODO: Make it private
    LifeDisplay *lifeDisplay = nullptr;
    QGraphicsProxyWidget *lifeDisplayer = nullptr; // TODO: Make it private
    QGraphicsScene* scene = nullptr;
    Player * player = nullptr;


public:

    // Constructor and destructor
    Game();
    ~Game();

    // Getters
    float getGroundLevel();
    int getStartOffset();
    int getEndOffset();
    int getSceneWidth();
    int getSceneHeight();


private:
    // Logic
    void init();
    void startCurrentLevel();
    void handleNewLevel();
    void toggleMenu();
    void close();

    // Helpers
    void clearMap();
    void createMap();
    void moveWithPlayer();
    void mapDisplayersToScene();
    void addElement(QGraphicsPixmapItem *element);

private slots:
    // Slots
    void handlePlayerMovement();
    void KeyPressEvent(QKeyEvent *event);
    void handleStateChange();

    // Friends
    friend int main(int argc, char *argv[]);
};

extern Game *game;

#endif // GAME_H
