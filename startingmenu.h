#ifndef STARTINGMENU_H
#define STARTINGMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class StartingMenu : public QWidget {
    Q_OBJECT

public:
    explicit StartingMenu(QWidget *parent = nullptr);
    ~StartingMenu();

private:
    QLabel *gameTitle = nullptr;    // Displays the game name
    QPushButton *startButton = nullptr; // Start button
    QPushButton *exitButton = nullptr;   // Exit button

    void setupUI();       // Sets up the UI layout

private slots:
    void startGame();     // Slot for starting the game
    void exitGame();      // Slot for exiting the game

signals:
    void startGameSignal(); // Signal to start the game
    void exitGameSignal(); // Signal to exit the game
};

#endif // STARTINGMENU_H
