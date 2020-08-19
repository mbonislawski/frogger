#ifndef LOSERECT_H
#define LOSERECT_H

#include <QGraphicsRectItem>
#include <QObject>

class LoseRect:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    LoseRect(int posX);
    int position;
public slots:
    void checkCollision();
};

#endif // LOSERECT_H
