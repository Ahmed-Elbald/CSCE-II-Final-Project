#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "spritesheet.h"
#include "settingsmanager.h"
#include "utils.h"


extern SettingsManager SM;

class Enemy : public SpriteSheet
{

    QVector<QPixmap> spriteSheetImages;
    QTimer *walkTimer = nullptr;
    QTimer *checkPlayerTimer = nullptr;
    int const walkSpeed = SM.settings->value("enemy/walkSpeed").toInt();
    int const walkRange = SM.settings->value("enemy/walkRange").toInt();
    int const fightRange = SM.settings->value("enemy/fightRange").toInt();
    int const checkPlayerInterval = SM.settings->value("enemy/checkPlayerInterval").toInt();
    int const walkTimerInterval = SM.settings->value("enemy/walkTimerInterval").toInt();
    EnemyActions currentState = ENEMY_DIE;
    // TODO : change it to Direction
    PlayerDirections direction = LEFT ; // Default direction

public:
    Enemy(qreal x , qreal y , qreal scale);
    ~Enemy();

    int type() const override { return EnemyType; }

    void changeState(EnemyActions newState);
    void loadSpriteSheetImages();
    void stopWalking();
    void walkLeft();
    void walkRight();
    void checkPlayer();
    void fight();
    void die();
    void beaten();
    void changeDirection(PlayerDirections newDirection);
};

#endif // ENEMY_H
