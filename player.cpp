#include "player.h"
#include "qaudiooutput.h"
#include <QDebug>
#include <QKeyEvent>
#include <game.h>

extern Game *game;

Player::Player() {

    // Load audio files
    jumpSound = new QMediaPlayer();
    jumpSound->setAudioOutput(new QAudioOutput());
    jumpSound->setSource(QUrl("qrc:/Assets/audio/man_jumps_1.wav"));
    walkSound = new QMediaPlayer();
    walkSound->setAudioOutput(new QAudioOutput());
    walkSound->setSource(QUrl("qrc:/Assets/audio/man_walks.wav"));


    // Loading the sprite sheets
    for(int i = 0; i < PLAYER_ACTIONS.size(); i++) {
        QString filename = PLAYER_ACTIONS[i];
        filename[0] = filename[0].toUpper();
        QString path = QString(":/Assets/images/Fighter/%1.png").arg(filename);
        spriteSheets.push_back(SpriteSheet(PLAYER_ACTIONS[i], path));
    }

    // Setting up the timer
    horizontalMovementTimer = new QTimer(this);
    connect(horizontalMovementTimer, SIGNAL(timeout()), this, SLOT(handleHorizontalMovement()));
    horizontalMovementTimer->start(16);

    jumpTimer = new QTimer(this);

    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Player::updateSpriteFrame);
    spriteTimer->start(75); // Update every 100ms

    updateSpriteFrame();

}

void Player::keyPressEvent(QKeyEvent *event) {
    bool stateChanged = false;

    // Add attack action
    if (event->key() == Qt::Key_A) {
        currentActions.insert(ATTACK_3);
        stateChanged = true;
    }
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        if (!keysPressed.contains(event->key())) {
            keysPressed.insert(event->key());
            currentActions.insert(WALK);
            stateChanged = true;
        }
    }
    if (event->key() == Qt::Key_Shift && (keysPressed.contains(Qt::Key_Right) || keysPressed.contains(Qt::Key_Left))) {
        if (!keysPressed.contains(event->key())) {
            keysPressed.insert(event->key());
            currentActions.insert(RUN);
            stateChanged = true;
        }
    }
    if (event->key() == Qt::Key_Space && !currentActions.contains(JUMP)) {
        handleJumping(currentActions.contains(WALK));
        stateChanged = true;
        // Add jump sound
        jumpSound->stop();
        jumpSound->play();
    }

    if (stateChanged) {
        setCurrentSprite();
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    bool stateChanged = false;

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        if (keysPressed.contains(event->key())) {
            keysPressed.remove(event->key());
            currentActions.remove(WALK);
            stateChanged = true;

        }
    }
    if (event->key() == Qt::Key_Shift) {
        if (keysPressed.contains(event->key())) {
            keysPressed.remove(event->key());
            currentActions.remove(RUN);
            stateChanged = true;
        }
    }

    if (stateChanged) {
        setCurrentSprite();
    }
}
void Player::setCurrentSprite() {
    PlayerActions newDominantAction;
    if (currentActions.contains(ATTACK_3)) {
        newDominantAction = ATTACK_3;
    } else if (currentActions.contains(JUMP)) {
        newDominantAction = JUMP;
    } else if (currentActions.contains(RUN)) {
        newDominantAction = RUN;
    } else if (currentActions.contains(WALK)) {
        newDominantAction = WALK;
    } else {
        newDominantAction = IDLE;
    }
    dominantAction = newDominantAction;
}

void Player::updateSpriteFrame() {
    if (dominantAction == PlayerActions::WALK || dominantAction == PlayerActions::RUN || dominantAction == PlayerActions::IDLE) {
        // qDebug() << "Called Inside\n" << currentSpriteFrame << ' ' << spriteSheets[dominantAction].frameCount << '\n';
        currentSpriteFrame = (currentSpriteFrame + 1) % spriteSheets[dominantAction].frameCount; // Loop the walk animation
        // qDebug() << "Called Inside\n" << currentSpriteFrame << ' ' << spriteSheets[dominantAction].frameCount << '\n';
    } else if (dominantAction == PlayerActions::JUMP || dominantAction == PlayerActions::ATTACK_3) {
        if (currentSpriteFrame < spriteSheets[dominantAction].frameCount - 1) {
            currentSpriteFrame++; // Only progress for one-time actions
        } else {
            currentActions.remove(dominantAction);
        }
    }

    // Set the new sprite frame
    // setCurrentSprite();
    setPixmap(spriteSheets[dominantAction].pixmap.copy(currentSpriteFrame * spriteSheets[dominantAction].frameWidth, 0, spriteSheets[dominantAction].frameWidth, spriteSheets[dominantAction].frameHeight));
}

void Player::handleHorizontalMovement() {

    if (currentActions.contains(JUMP)) return;
    int shift = 3;
    if (keysPressed.contains(Qt::Key_Shift)) {
        shift = 5;
        currentActions.insert(PlayerActions::RUN);
    }
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right)) {
        // Replay the walking sound when it ends
        if (walkSound->playbackState() == QMediaPlayer::PlaybackState::StoppedState) {
            walkSound->play();
        }
    } else {
        walkSound->stop();
    }
    if (keysPressed.contains(Qt::Key_Left)) {
        // Check if new position will make the palyer go out of the screen
        if (x() - shift <= 100) {
            currentActions.remove(WALK);
            currentActions.remove(RUN);
            setCurrentSprite();

            return;
        }
        if (direction == 1) {
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
            direction = -1;
        }
        setPos(x() - shift, y());
        emit playerPositionChanged();
    } else if (keysPressed.contains(Qt::Key_Right)) {
        if (x() + shift >= game->scene->width() - boundingRect().width() - 100) {
            currentActions.remove(WALK);
            currentActions.remove(RUN);
            setCurrentSprite();

            return;
        }
        if (direction == -1) {
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
            direction = 1;
        }
        // Check if new position will make the palyer go out of the screen
        if (x() + shift > game->scene->width() - boundingRect().width() - 100) {

            return;
        }
        emit playerPositionChanged();
        setPos(x() + shift, y());
    }

}

void Player::handleJumping(bool moveHorizontally) {
    currentActions.insert(JUMP);
    verticalVelocity = jumpVelocity; // Set the initial jump speed
    // disconnect timer and start it again
    jumpTimer->disconnect();
    jumpTimer->connect(jumpTimer, &QTimer::timeout, this, [=](){
        updateJump(moveHorizontally);
    });
    jumpTimer->start(16);
}

void Player::updateJump(bool moveHorizontally) {
    // Update the player's vertical velocity (gravity effect)
    verticalVelocity += gravity;

    // Move the player by the current vertical velocity
    setY(y() + verticalVelocity);

    // Move the player horizontally if needed
    if (moveHorizontally) {
        setX(x() + direction * 3);
        emit playerPositionChanged();
    }

    // Stop the jump when the player lands (y position >= ground level)
    // Assuming ground; level is y = 300 (adjust as needed)
    if (y() >= game->height() * 0.88 - boundingRect().height()) {
        setY(game->height() * 0.88 - boundingRect().height());              // Reset to ground level
        currentActions.remove(JUMP);
        jumpTimer->stop();      // Stop the jump timer
        verticalVelocity = 0;   // Reset the velocity
        setCurrentSprite();
    }
}

void Player::handleAttack() {

}
