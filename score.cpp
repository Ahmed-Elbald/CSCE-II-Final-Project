#include "score.h"
#include <QFont>
#include <QGraphicsPixmapItem>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    // Initialize the score to 0
    scoreCount = 0;

    // Set the initial score display
    setPlainText(QString("Score : ") + QString::number(scoreCount));
    setDefaultTextColor(Qt::black);// set color
    setFont(QFont("Impact", 16));  // set font


    // * the image didn't look good, so I'll leave this for later (maybe i can find a better image) *

    // // Add the image to represent "Score:"
    // QPixmap scaledPixmap = QPixmap(":/Assets/images/scoretext.png").scaled(50, 50);
    // QGraphicsPixmapItem* scoreImage = new QGraphicsPixmapItem(scaledPixmap);
    // scoreImage->setParentItem(this); // Attach it as a child *parent is score* (to keep them grouped) this makes its postion "relative" to the score text

    // // Position the image relative to the score value
    // qreal imageWidth = scaledPixmap.width();
    // qreal imageHeight = scaledPixmap.height();
    // qreal textHeight = boundingRect().height();

    // scoreImage->setPos(
    //     -imageWidth - 10,                             // Slightly left of the text
    //     (textHeight / 2) - (imageHeight / 2)         // Centered vertically with the text
    //     );


}

void Score::increase() {

    setScore(scoreCount + 5);  // increases the count by  5
}
void Score::big_increase() { // for stronger enemies

    setPlainText(QString::number(scoreCount + 25));  // increases the count by 25
}
void Score::decrease() {
    // decrement the score and update the display

   if (scoreCount > 0)  // ensure it doesn't go negative
    setPlainText(QString::number(scoreCount - 5));  // decreases the count by 5
}

void Score::big_decrease() {
    // decrement the score and update the display

    if (scoreCount > 0)
    setPlainText(QString::number(scoreCount - 5));  // decreases the count by 25
}

void Score::setScore(int newValue)
{
        if (newValue < 0)
            throw std::invalid_argument("Score cannot be negative");

        scoreCount = newValue;
        setPlainText(QString("Score : ") + QString::number(scoreCount));


}


int Score::getScore() {
    return scoreCount;
}
