#include "utils.h"
#include <random>

const QVector<QString> PLAYER_ACTIONS = {
    "idle",
    "walk",
    "run",
    "jump",
    "die",
};


int RandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}
