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
    PowerUpType
};

enum AnimationType {
    oneTime,
    repeating
};

extern const QVector<QString> PLAYER_ACTIONS;

int RandomNumber(int min, int max) ;
#endif // UTILS_H
