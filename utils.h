#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QVector>
#include <QGraphicsItem>

enum PlayerActions {
    IDLE,
    WALK,
    RUN,
    JUMP,
    DIE,
};

enum PlayerDirections {
    LEFT = -1,
    RIGHT = 1
};

enum CustomTypes {
    BlockType = QGraphicsItem::UserType + 1,
    TrapType,
    ShieldType,
    CoinType,
    EnemyType,
    HealthPotionType
};

enum AnimationType {
    oneTime,
    repeating
};

enum EnemyActions {
    ENEMY_IDLE,
    ENEMY_WALK,
    ENEMY_BEATEN,
    ENEMY_FIGHT,
    ENEMY_DIE,
};

extern const QVector<QString> PLAYER_ACTIONS;

extern const QVector<QString> ENEMY_ACTIONS;


int RandomNumber(int min, int max) ;
#endif // UTILS_H
