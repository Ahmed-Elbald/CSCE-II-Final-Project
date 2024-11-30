#include "spritesheet.h"
#include "qtimer.h"
#include "settingsmanager.h"


// Static variables
QTimer *SpriteSheet::animationTimer = nullptr;
QList<SpriteSheet*> SpriteSheet::instances;

// Static functions
void SpriteSheet::advanceAllFrames() {
    for (SpriteSheet* instance : instances) {
        instance->advanceFrames();
    }
}

// Constructor
SpriteSheet::SpriteSheet(QString name, AnimationType type) {
    this->name = name;
    this->type = type;

    // Add this instance to the list
    instances.append(this);

    // Initialize and start the shared timer if it hasn't been started already
    if (animationTimer == nullptr) {
        animationTimer = new QTimer(this);
        connect(animationTimer, &QTimer::timeout, this, &SpriteSheet::advanceAllFrames);
        animationTimer->start(SM.settings->value("spriteUpdateInterval").toInt());
    }
}


// Logic
void SpriteSheet::setProperties(int frameWidth, int frameHeight, int xOffset, int yOffset, int contentWidth, int contentHeight) {
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->contentOffsetX = xOffset;
    this->contentOffsetY = yOffset;
    this->contentWidth = contentWidth;
    this->contentHeight = contentHeight;
}

void SpriteSheet::setSpritePixmap(QPixmap pix, AnimationType type) {

    if (frameWidth == 0)
        throw std::runtime_error("Properties must be set before pixmap");

    // Reset frame
    currentSpriteFrame = 0;

    // Set new type
    this->type = type;

    // Set new pixmap
    originalPixmap = pix;

    // Calculate new frame count
    frameCount = pix.width() / frameWidth;

    // Set the first frame
    advanceFrames();

}


void SpriteSheet::advanceFrames() {
    // If it is a repeating action, loop the animation
    if (type == repeating)
        currentSpriteFrame = (currentSpriteFrame + 1) % frameCount;

    // If it is a one-time action, progress the animation once
    else {
        // If the animation is not done, progress
        if (currentSpriteFrame < frameCount - 1)
            currentSpriteFrame++;
    }

    // Make temp pixmap
    setPixmap(originalPixmap.copy(
            currentSpriteFrame * getFrameWidth() + getContentOffsetX(),
            getContentOffsetY(),
            getContentWidth(),
            getContentHeight()
        ));
}

// Getters
QString SpriteSheet::getName() { return name; }
int SpriteSheet::getFrameCount() { return frameCount; }
int SpriteSheet::getFrameWidth() { return frameWidth; }
int SpriteSheet::getFrameHeight() { return frameHeight; }
int SpriteSheet::getContentOffsetX() { return contentOffsetX; }
int SpriteSheet::getContentOffsetY() { return contentOffsetY; }
int SpriteSheet::getContentWidth() { return contentWidth; }
int SpriteSheet::getContentHeight() { return contentHeight; }

// Destructor
SpriteSheet::~SpriteSheet() {
    // Remove this instance from the list
    instances.removeAll(this);

    // Stop and delete the timer if there are no more instances
    if (instances.isEmpty() && animationTimer != nullptr) {
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;
    }
}
