#include "life.h"
#include <QGridLayout>
#include <QPixmap>
#include <algorithm> // Ensure for std::max

life::life(State* state, QGraphicsItem* parent)
    : QGraphicsItem(parent), state(state) {

    // Load the heart images
    fullHeart = QPixmap(":/Assets/images/full_heart.png");
    halfHeart = QPixmap(":/Assets/images/half_heart.png");
    emptyHeart = QPixmap(":/Assets/images/empty_heart.png");

    if (fullHeart.isNull() || halfHeart.isNull() || emptyHeart.isNull()) {
        qWarning() << "Failed to load heart images.";
    }

    maxWidth = std::max( std::max(fullHeart.width(), halfHeart.width()) , emptyHeart.width() );
    maxHeight = std::max( std::max(fullHeart.height(), halfHeart.height()) , emptyHeart.height() );
    // layout = new QGridLayout(this);

    // // Initialize the heart display with ful hearts
    // for (int i = 0; i < 5; ++i) {
    //     hearts[i] = new QLabel(this);
    //     hearts[i]->setPixmap(fullHeart);
    //     layout->addWidget(hearts[i], 0, i);  // Arrange hearts in a row
    // }

    // // Connect the stateChanged signal to update the heart display
    // connect(state, &State::stateChanged, this, &life::updateLives);
}

// void life::setlives(int lives) {
//     // NumOfFullHearts= lives;
//     // NumOfemptyHearts= NumOfLives - lives;
//     // update(); // Request redraw for the health bar

//     // *will implement the half heart idea later*
//     // // lives =0 will be "game over"
//     // // Determine the number of full, half, and empty hearts
//     // int fullHearts = static_cast<int>(lives); // integer part represents the full hearts
//     // int halfHearts = (lives - fullHearts >= 0.5) ? 1 : 0; // Half heart if fractional part >= 0.5
//     // // int emptyHearts = 5 - fullHearts - halfHearts; // Remaining hearts are empty (the lost ones of the 5)
// }
void life::increaseLives() {

    updateLives(NumOfFullHearts++);
}
void life::decreaseLives() {
    if (NumOfFullHearts > 0) { //make sure it does not go negative
        updateLives(NumOfFullHearts--);
    }
}
void life::updateLives(int PlayerLives) {
    NumOfFullHearts= PlayerLives;
    NumOfemptyHearts= NumOfLives - PlayerLives;
   //update(); // Trigger a redraw
    update(boundingRect()); // This will trigger the paint function
    // float lives = state->getLives(); // between 1.0 and 5.0 (the 0.5 stands for half a life)


    // // Update the display (loop over the hearts)
    // for (int i = 0; i < 5; ++i) {
    //     if (i < fullHearts) { // show full hearts at the beginning
    //         hearts[i]->setPixmap(fullHeart);
    //     } else if (i < fullHearts + halfHearts) { // followed by the halfs
    //         hearts[i]->setPixmap(halfHeart);
    //     } else {
    //         hearts[i]->setPixmap(emptyHeart);
    //     }
    // }
    /*ex: lives = 3.5
    full hearts = 3
        half hearts = 1
        empty h = 1

        loop
            i=0
        shows the 3 full one (until i =2)
        i=3
          shows one half
              after the it just fills the remaining positions with empty hearts
          */
}

QRectF life::boundingRect() const {
    // Define the rectangle that encloses the health bar

   // int maxWidth = std::max( std::max(fullHeart.width(), halfHeart.width()) , emptyHeart.width() );
    //int maxHeight = std::max( std::max(fullHeart.height(), halfHeart.height()) , emptyHeart.height() );

    return QRectF(0, 0, NumOfLives *maxWidth, maxHeight);

       // int totalWidth = NumOfLives * (maxWidth + 5) - 5; // Total width (include spacing, minus last gap)


}

void life::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    for (int i = 0; i < NumOfLives; ++i) {
        QPixmap heartImage;

        if (i < NumOfFullHearts) { // show full hearts at the beginning
            heartImage = fullHeart;
        } /*else if (i < NumOfFullHearts +NumOfhalfHearts) {// followed by the halfs
            heartImage = halfHeart;
        }*/ else { // the rest is empty
            heartImage = emptyHeart;
        }

        // Draw each heart with some spacing
        int x = i * ( maxWidth+ 5);
        painter->drawPixmap(x, 0, heartImage);


    }
}
