#ifndef CAR_H
#define CAR_H

#include <QGraphicsRectItem>
#include <QObject>

class Car: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Car();
    int size;
    int position;
public slots:
    void move();
    void checkCarsCollision();
};

#endif // CAR_H
