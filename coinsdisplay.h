#ifndef COINSDISPLAY_H
#define COINSDISPLAY_H
#include <QGraphicsTextItem>

class CoinsDisplay: public QGraphicsTextItem
{
public:

    // Constructor and Destructor
    CoinsDisplay(int initialValue = 0, QGraphicsItem * parent=0);
    ~CoinsDisplay();

    // Setters
    void set(int);
    void increment();
    void decrement();

private:

    // Varibles
    int value = 0;

    // UI
    QGraphicsPixmapItem * coinImage = nullptr;

private:
    // Helpers
    void updateText();
};

#endif // COINSDISPLAY_H
