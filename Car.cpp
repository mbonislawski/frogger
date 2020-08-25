#include "Car.h"
#include <QTimer>
#include <QList>
#include <stdlib.h>

#include <Game.h>

extern Game * game;

Car::Car(): QObject(), QGraphicsRectItem(){

    //set random position
    srand ( (unsigned)time(NULL) );
    QVector<int> posArray{150, 300, 450, 600, 750};
    int random_number = rand() % 5;
    if (random_number == game->lastCarPos) {
        random_number = rand() % 5;
    } else {
        position = random_number;
        game->lastCarPos = random_number;
    }

    setPos(0, posArray[random_number]);

    // drew the Car rect
    QVector<int> sizeArray{100, 150, 200};
    srand ( (unsigned)time(NULL) );
    int random_size = rand() % 3;
    if (random_size == game->lastCarType) {
        random_size = rand() % 3;
    } else {
        size = random_size;
        game->lastCarType = random_size;
    }

    size = sizeArray[random_size];
    setRect(-300,0, size ,100);

    if (random_size == 1) {
        this->setBrush(Qt::blue);
    } else if (random_size == 2) {
        this->setBrush(Qt::yellow);
    } else {
        this->setBrush(Qt::magenta);
    }

    QTimer * timer = new QTimer(this);
    QTimer * timerCollision = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timerCollision,SIGNAL(timeout()),this,SLOT(checkCarsCollision()));
    timerCollision->start();
    timer->start(10 / game->level);
}

void Car::move() {
    setPos(x() + 1, y());
    if (pos().x() > 1800) {
        scene()->removeItem(this);
        delete this;
    }
}

void Car::checkCarsCollision() {
    // if Car collides with Car
    QList<QGraphicsItem *> colliding_items = scene()->collidingItems(this);

    for (int i = 0, n = colliding_items.size(); i < n;  ++i) {
        if (colliding_items[i]->flags().testFlag(ItemIsFocusable)) {
            game->displayGameOverWindow("Game is over");
        } else {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
        }
    }
}
