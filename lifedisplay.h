#ifndef LIFEDISPLAY_H
#define LIFEDISPLAY_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "State.h"
class LifeDisplay: public QWidget
{


    public:
        LifeDisplay(State* State, QWidget* parent = nullptr);

        void updateLives();
    private:
        State* state;                  // The player's state (lives)
        QLabel* hearts[5];             // Array of QLabel to display hearts
        int MaxNumOfLives =5;
        QPixmap fullHeart;             // Image for a full heart
        QPixmap emptyHeart;            // Image for an empty heart
       QGridLayout* layout;           // Layout to arrange the hearts in a row


};

#endif // LIFEDISPLAY_H




