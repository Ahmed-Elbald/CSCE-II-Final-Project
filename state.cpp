#include "state.h"
#include "game.h"

State::State() {
    qDebug() << "From state constructor";
    qDebug() << (game == nullptr);
}

// Getters
int State::getCoins() { return coins; }
int State::getScore() { return score; }
int State::getLives() { return lives; }
int State::getLevel() { return level; }
bool State::getIsGameOver() { return isGameOver; }
bool State::getIsPaused() { return isPaused; }

// Setters
void State::setCoins(int coins) {
    if (coins < 0)
        throw std::invalid_argument("Coins cannot be negative");
    this->coins = coins;
    emit stateChanged();
}
// void State::setScore(int score) {
//     if (score < 0)
//         throw std::invalid_argument("Coins cannot be negative");
//     this->score = score;
//     emit stateChanged();
// }
void State::setLives(int lives) {
    qDebug() << "From set lives" << lives;
    if (lives < 0 || lives > 5)
        throw std::invalid_argument("Lives must be between 1 and 5");
    this->lives = lives;
    emit stateChanged();
}
void State::setLevel(int level) {
    qDebug() << "From set level";
    if (level < 1 || level > 5)
        throw std::invalid_argument("Level must be between 1 and 5");
    this->level = level;
    emit stateChanged();
}

void State::setIsGameOver(bool isGameOver) { this->isGameOver = isGameOver; emit stateChanged(); }
void State::setIsPaused(bool isPaused) { this->isPaused = isPaused; emit stateChanged(); }
void State::incrementCoins() { setCoins(getCoins() + 1); emit stateChanged(); }
void State::decrementCoins() { setCoins(getCoins() - 1); emit stateChanged(); }
//void State::incrementScore() { scorePtr->increase(); emit stateChanged(); }
//void State::decrementScore() { scorePtr->decrease(); emit stateChanged(); }

void State::decrementLives() { setLives(getLives() - 1); emit stateChanged(); }
void State::incrementLives() { setLives(std::min(getLives() + 1, 5)); emit stateChanged(); } // max is five lives




