#include <QVBoxLayout>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "startingmenu.h"
#include "game.h"
#include "soundplayer.h"

extern Game *game;

StartingMenu::StartingMenu(QWidget *parent) : QWidget(parent) {
    setupUI();

    // Connect buttons to respective slots
    connect(startButton, &QPushButton::clicked, this, &StartingMenu::startGame);
    connect(exitButton, &QPushButton::clicked, this, &StartingMenu::exitGame);
}

void StartingMenu::setupUI() {
    // Set window properties
    this->setWindowTitle("RUN - Starting Menu");
    this->resize(800, 600);

    // Add background image
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/Assets/images/bg_1.jpg")));
    this->setPalette(palette);
    setAutoFillBackground(true); // Ensure the background is drawn

    // Create title
    gameTitle = new QLabel("RUN", this);
    gameTitle->setAlignment(Qt::AlignCenter);
    gameTitle->setStyleSheet("font-size: 36px; font-weight: bold; color: white;");

    // Create buttons
    startButton = new QPushButton("Start", this);
    exitButton = new QPushButton("Exit", this);

    // Style the buttons
    QString buttonStyle = "font-size: 18px; padding: 10px; border: 2px solid white; "
                          "border-radius: 10px; color: white; background-color: rgba(0, 0, 0, 0.6);";
    startButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // Set button fixed width (half the window width)
    int buttonWidth = this->width() / 2;
    startButton->setFixedWidth(buttonWidth);
    exitButton->setFixedWidth(buttonWidth);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(gameTitle);
    layout->addStretch();

    // Add buttons to the layout and center them
    QHBoxLayout *startButtonLayout = new QHBoxLayout();
    startButtonLayout->addStretch();
    startButtonLayout->addWidget(startButton);
    startButtonLayout->addStretch();

    QHBoxLayout *exitButtonLayout = new QHBoxLayout();
    exitButtonLayout->addStretch();
    exitButtonLayout->addWidget(exitButton);
    exitButtonLayout->addStretch();

    layout->addLayout(startButtonLayout);
    layout->addLayout(exitButtonLayout);
    layout->addStretch();

    setLayout(layout);

    setLayout(layout);
}

void StartingMenu::startGame() {
    SP.buttonClickSound->play();
    emit startGameSignal();
}


void StartingMenu::exitGame() {
    SP.buttonClickSound->play();
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Exit", "Are you sure you want to exit?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        emit exitGameSignal();
}

StartingMenu::~StartingMenu() {
    if (gameTitle != nullptr)
        delete gameTitle;
    if (startButton != nullptr)
        delete startButton;
    if (exitButton != nullptr)
        delete exitButton;
}
