#ifndef CAR_H
#define CAR_H

#include <QGraphicsRectItem>
#include <QObject>

class Car: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Car();
    int position;
public slots:
    void move();
    void checkCarsCollision();
private:
    QVector<int> posArray = {150, 300, 450, 600, 750};
    QVector<int> sizeArray = {100, 150, 200};
    int size;
    void setColor();
    int getSize();
    void setSize(int size);
};

#endif // CAR_H
