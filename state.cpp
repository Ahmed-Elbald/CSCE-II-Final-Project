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
void State::increamentLives() { setLives(getLives() + 1); emit stateChanged(); }

/* call update updateLives() and send the updated lives to it

the half heart approach:
 - if the player hits a small enemy or gets a small reward , they will lose/gain half a life
 - the "lives" variable will need to be changed to float
 - the following two function will be added to increment/decrement half a life:

void State::decrement_half_Lives() { setLives(getLives() - 0.5); emit stateChanged(); }
void State::increament_half_Lives() { setLives(getLives() + 0.5); emit stateChanged(); }

*/
