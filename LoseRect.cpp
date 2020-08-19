#include <Frog.h>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QtDebug>
#include <Car.h>
#include <LoseRect.h>
#include <QTimer>
#include <QPainter>
#include <QGraphicsView>
#include <Game.h>

extern Game * game;

LoseRect::LoseRect(int posX): QObject(), QGraphicsRectItem(){
    this->setRect(0,0,98,98);
    this->setBrush(Qt::gray);
    this->setFlag(ItemIsPanel);
    this->setPos(posX, 0);
}

void LoseRect::checkCollision() {
    // if frog colides with the win point, start next level
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n;  ++i) {
        if (colliding_items[i]->flags().testFlag(ItemIsFocusable)) {
            game->displayGameOverWindow("Game is over");
        }
    }
}
