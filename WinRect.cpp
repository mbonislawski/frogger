#include <Frog.h>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QtDebug>
#include <Car.h>
#include <WinRect.h>
#include <QTimer>
#include <QPainter>
#include <QGraphicsView>
#include <Game.h>

extern Game * game;

WinRect::WinRect(): QObject(), QGraphicsRectItem(){
    this->setRect(0,0,100,100);
    this->setBrush(Qt::green);
    int randomPosition = rand() % 1500;
    this->setPos(randomPosition, 0);
}

void WinRect::checkCollision() {
    // if frog colides with win point, start next level
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n;  ++i) {
        this->setBrush(Qt::red);
        if (colliding_items[i]->flags()) {
            game->displayGameOverWindow("Game is over");
        } else {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
        }
    }
}
