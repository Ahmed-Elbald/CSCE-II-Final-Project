#include "healthpotion.h"


HealthPotion::HealthPotion(qreal x, qreal y, qreal scale,  QString path)
{
    QPixmap pix = QPixmap(path);
    qDebug() << pix.width() << pix.height() ;
    setPixmap(pix);
    setPos(x, y );
    setScale(scale);
    qDebug() << "HealthPotion created at " << x << " " << y;

}

HealthPotion::~HealthPotion()
{
    qDebug() << "HealthPotion deleted";
}

// type
int HealthPotion::type() const
{
    return HealthPotionType;
}