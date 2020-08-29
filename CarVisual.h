#ifndef CAR_H
#define CAR_H

#include <QGraphicsRectItem>
#include <QObject>

class CarVisual: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    CarVisual();
    int size;
    int position;
public slots:
    void move();
    void checkCarsCollision();
};

#endif // CAR_H
