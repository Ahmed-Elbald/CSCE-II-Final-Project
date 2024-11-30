#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{

public:
    Score(QGraphicsItem * parent=0);
    void increase();
    void big_increase();
    void decrease();
    void big_decrease();
    void setScore(int);
    int getScore();


private:
    int scoreCount;
};
#endif // SCORE_H
