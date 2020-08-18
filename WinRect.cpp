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
        if (colliding_items[i]->flags()) {
            game->runNextLevel();
        } else {
            srand ( (unsigned)time(NULL) );
            int randomPosition = rand() % 1500;
            this->setPos(randomPosition, 0);
        }
    }
}
