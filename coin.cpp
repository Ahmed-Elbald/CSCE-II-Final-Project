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
    setProperties( SM.settings->value("coin/spriteFrameWidth").toInt(),
                    SM.settings->value("coin/spriteFrameHeight").toInt(),
                    SM.settings->value("coin/spriteContentOffsetX").toInt(),
                    SM.settings->value("coin/spriteContentOffsetY").toInt(),
                    SM.settings->value("coin/spriteContentWidth").toInt(),
                    SM.settings->value("coin/spriteContentHeight").toInt());
    setSpritePixmap(QPixmap(spriteSheetPath));
    // Set the position
    setPos(x , y);
    // Set the scale
    setScale(scale);
    // Set the value
    this->value = value;
}

qreal Coin::getValue() const
{
    return value;
}
