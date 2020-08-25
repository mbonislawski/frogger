#include <LoseRect.h>
#include <QPainter>
#include <Game.h>

extern Game * game;

LoseRect::LoseRect(int posX): QObject(), QGraphicsRectItem(){
    this->setRect(0,0,98,98);
    this->setBrush(Qt::gray);
    this->setFlag(ItemIsPanel);
    this->setPos(posX, 0);
}

void LoseRect::checkCollision() {
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n;  ++i) {
        if (colliding_items[i]->flags().testFlag(ItemIsFocusable)) {
            game->displayGameOverWindow("Game is over");
        }
    }
}
