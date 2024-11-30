#ifndef LIFE_H
#define LIFE_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include "State.h"
// #include "qgridlayout.h"
// #include "qlabel.h"
class life: public QGraphicsItem
{


    public:
        life(State* State, QGraphicsItem* parent = nullptr);
        //~life();
        void updateLives(int PlayerLives);
        QRectF boundingRect() const override; // Define bounding box
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        // void setlives(int lives);
        void increaseLives();
        void decreaseLives();

    private:
        State* state;                  // The player's state (lives)
        static const int NumOfLives =5;
       // QLabel* hearts[NumOfLives];             // Array of QLabel to display hearts
        QPixmap fullHeart;             // Image for a full heart
        QPixmap halfHeart;             // Image for a half heart
        QPixmap emptyHeart;            // Image for an empty heart
        int NumOfFullHearts =0;
        int NumOfhalfHearts =0;
        int NumOfemptyHearts=0;
       //QGridLayout* layout;           // Layout to arrange the hearts in a row

        int maxWidth ;
        int maxHeight ;

};

#endif // LIFE_H




