#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "shieldeffect.h"
#include "settingsmanager.h"
#include "spritesheet.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include "sound.h"
#include <QKeyEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QTime>

class Player : public SpriteSheet
{
private:
    Q_OBJECT
    // Constants
    const int startOffset = SM.settings->value("window/defaultStartOffset").toInt();
    const int walkShift = SM.settings->value("player/walkSpeed").toInt();
    const int runShift = SM.settings->value("player/runSpeed").toInt();

    const int walkTimerInterval = SM.settings->value("player/walkTimerInterval").toInt();
    const int jumpTimerInterval = SM.settings->value("player/jumpTimerInterval").toInt();
    const int fallTimerInterval = SM.settings->value("player/fallTimerInterval").toInt();
    const int collisionTimerInterval = SM.settings->value("player/collisionTimerInterval").toInt();

    const float jumpVelocity = SM.settings->value("player/jumpSpeed").toFloat();
    const float gravity = SM.settings->value("player/gravity").toFloat();

    // Variables
    float verticalVelocity = 0.0f;

    PlayerDirections direction = RIGHT;

    QSet<int> keysPressed;
    PlayerActions dominantAction = IDLE;

    QVector<QPixmap> spriteSheetImages;

    // Flags
    bool isWalking = false;
    bool isRunning = false;
    bool isJumping = false;
    bool isFalling = false;
    bool isDying = false;
    bool hasShield = false;

    // Timers
    QTimer *jumpTimer = nullptr;
    QTimer *fallTimer = nullptr;
    QTimer *walkTimer = nullptr;
    QTimer *collisionTimer = nullptr;

    // UI
    ShieldEffect * shield = nullptr;

public:
    // Constructor and destructor
    Player();
    ~Player();

    // Logic
    void startLevel();
    void activate();
    void deactivate();

    // Setters
    void setDominantAction(PlayerActions action);
    int xCenter(); // Center of the player on the x-axis
private:

    // Logic
    void init();

    // Walking
    void handleWalking();
    void walk();
    void stopWalking();

    // Jumping
    void handleJumping();
    void jump(int = 0);

    // Falling
    void handleFalling(int = 0);
    void fall(int = 0);
    void stopFalling();

    // Dying
    void handleDying();
    void die();
    void stopDying();

    // Collision
    void handleCollision();
    void handleCoinCollision(QGraphicsItem*);
    void handleShieldCollision(QGraphicsItem*);
    void handleHealthPotionCollision(QGraphicsItem*);
    void handleDangerCollision(QGraphicsItem*);

    // Shields
    void enableShield();
    void disableShield();

    // Helpers
    void loadSpriteSheetImages();
    void changeDirection(PlayerDirections);
    void setCurrentSprite();
    void hide();
    void show();
    double findBestPosition(double, double, double);
    QGraphicsItem* validateNewPosition(double = 0, double = 0);
    void moveToStartOver();

signals:
    // Signals
    void playerPositionChanged();

private slots:
    // Slots
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
};

#endif // PLAYER_H
