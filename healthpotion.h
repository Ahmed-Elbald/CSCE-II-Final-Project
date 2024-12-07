#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "utils.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class HealthPotion :public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    HealthPotion( qreal x , qreal y , qreal scale ,QString path);
    int type() const override;
    ~HealthPotion();

};

#endif // HEALTHPOTION_H
