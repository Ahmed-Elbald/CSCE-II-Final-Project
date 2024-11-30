#ifndef COIN_H
#define COIN_H
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "sound.h"
#include "spritesheet.h"


class  Coin :  public SpriteSheet
{
Q_OBJECT
private:
    qreal value;
    Sound *coinSound;
    static QStringList soundPaths;
    static qreal volume;
    // Helper functions
    void setRandomSound();

public:
    Coin( qreal x , qreal y , qreal scale , qreal value, QString spriteSheetPath);
    qreal getValue() const;
    ~Coin() override;
    int type() const override {return CoinType;}

private:
    // Helper functions
    static QStringList getSoundPaths();
    static qreal getVolume();


};

#endif // COIN_H
