#include <QApplication>
#include "game.h"


Game * game = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    return a.exec();
}
