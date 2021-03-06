#include "Car.h"
#include <QTimer>
#include <QList>
#include <stdlib.h>

#include <Game.h>
#include <Level.h>

extern Game * game;

Car::Car(): QObject(), QGraphicsRectItem(){

    //set random position
    srand ( (unsigned)time(NULL) );
    int random_number = rand() % 5;
    if (random_number == game->lastCarPos) {
        random_number = rand() % 5;
    } else {
        position = random_number;
        game->lastCarPos = random_number;
    }

    setPos(0, posArray[random_number]);

    // drew the Car rect
    srand ( (unsigned)time(NULL) );
    int random_size = rand() % 3;
    if (random_size == game->lastCarType) {
        random_size = rand() % 3;
    } else {
        setSize(random_size);
        game->lastCarType = random_size;
    }

    setSize(sizeArray[random_size]);
    setRect(-300,0, size ,100);

    setColor();

    QTimer * timer = new QTimer(this);
    QTimer * timerCollision = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timerCollision,SIGNAL(timeout()),this,SLOT(checkCarsCollision()));
    timerCollision->start();
    timer->start(10 / game->level->getLevel());
}

void Car::move() {
    setPos(x() + 1, y());
    if (pos().x() > 1800) {
        scene()->removeItem(this);
        delete this;
    }
}

void Car::setSize(int size) {
    this->size = size;
}

int Car::getSize() {
    return this->size;
}

void Car::setColor() {
    if (getSize() == 100) {
        this->setBrush(Qt::blue);
    } else if (getSize() == 150) {
        this->setBrush(Qt::yellow);
    } else {
        this->setBrush(Qt::magenta);
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
