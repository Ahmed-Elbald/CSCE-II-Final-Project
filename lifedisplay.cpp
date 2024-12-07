#include "lifedisplay.h"
#include <QGridLayout>
#include <QPixmap>

LifeDisplay::LifeDisplay(State* state, QWidget* parent)
    : QWidget(parent), state(state) {

    // Set the heart images
    fullHeart = QPixmap(":/Assets/images/full_heart.png").scaled(40, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    emptyHeart = QPixmap(":/Assets/images/empty_heart.png").scaled(40, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    layout = new QGridLayout(this);

    this->setFixedSize(250, 70); // Set the fixed size of the widget
    this->setStyleSheet("background-color: transparent;");

    // Initialize the heart display with ful hearts
    for (int i = 0; i < 5; ++i) {
        hearts[i] = new QLabel(this);
        hearts[i]->setPixmap(fullHeart);
        layout->addWidget(hearts[i], 0, i, Qt::AlignCenter);  // Arrange hearts in a row and align

    }

    // Connect the stateChanged signal to update the heart display
    connect(state, &State::stateChanged, this, &LifeDisplay::updateLives);
}

void LifeDisplay::updateLives() {
    int lives = state->getLives(); // between 1 and 5
    // lives = 0 will be "game over"

    // Determine the number of full hearts
    int fullHearts = lives;

    // Update the display (loop over the hearts)
    for (int i = 0; i < 5; ++i) {
        if (i < fullHearts) { // show full hearts at the beginning
            hearts[i]->setPixmap(fullHeart);
        } else { // Remaining hearts are empty (the lost ones of the 5)
            hearts[i]->setPixmap(emptyHeart);
        }
    }
}

