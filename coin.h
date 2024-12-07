#ifndef COIN_H
#define COIN_H
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "spritesheet.h"


class  Coin :  public SpriteSheet
{
Q_OBJECT
private:
    qreal value;
    static QStringList soundPaths;
    static qreal volume;
public:
    Coin( qreal x , qreal y , qreal scale , qreal value, QString spriteSheetPath);
    qreal getValue() const;
    int type() const override {return CoinType;}

private:
    // Helper functions
    static QStringList getSoundPaths();
    static qreal getVolume();


};

#endif // COIN_H
