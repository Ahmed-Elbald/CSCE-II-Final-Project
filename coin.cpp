#include "coin.h"
#include "game.h"
#include <QString>


extern Game *game;

QStringList Coin::getSoundPaths() {
    static QStringList soundPaths = QStringList({
        SM.settings->value("audio/coinPickUp/1").toString(),
        SM.settings->value("audio/coinPickUp/2").toString(),
        SM.settings->value("audio/coinPickUp/3").toString()
    });
    return soundPaths;
}

qreal Coin::getVolume() {
    static qreal volume = SM.settings->value("audio/coin_volume").toReal();
    return volume;
}

Coin::Coin( qreal x , qreal y , qreal scale , qreal value, QString spriteSheetPath)
{
    // Set the image
    setProperties(20, 20, 2, 1, 19, 19);
    setSpritePixmap(QPixmap(spriteSheetPath));
    // Set the position
    setPos(x , y);
    // Set the scale
    setScale(scale);
    // Set the value
    this->value = value;
    // Set the sound
    setRandomSound();

}

Coin::~Coin()
{
    // Delete the coin
    coinSound->deleteLater();
}

void Coin::setRandomSound()
{
    // Set the sound
    int mx = getSoundPaths().size() - 1;
    this->coinSound = new Sound(getSoundPaths()[RandomNumber(0 ,mx)], getVolume() , QMediaPlayer::Loops::Once);
}

qreal Coin::getValue() const
{
    return value;
}
