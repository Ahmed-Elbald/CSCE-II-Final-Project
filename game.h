#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "coinsdisplay.h"
#include "level.h"
#include "player.h"
#include <QMediaPlayer>
#include "sound.h"
#include "state.h"
#include"score.h"
#include"life.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:

    // Trackers
    // Sounds
    Sound *victorySound, *levelWinSound;
    Sound *bgMusicPlayer;


    // UI
    QGraphicsPixmapItem *endFlag;

public:
    // TODO: Make them private and modify that everywhere
    QVector<QGraphicsPixmapItem*> elements;
    State *state = nullptr;
    Level *level = nullptr;
    CoinsDisplay *coinsDisplayer; // TODO: Make it private
    QGraphicsScene* scene = nullptr;
    Player * player = nullptr;
    Score * score;
    life* lifeptr;

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

    // Helpers
    void createMap();
    void moveWithPlayer();
    void mapDisplayersToScene();


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
