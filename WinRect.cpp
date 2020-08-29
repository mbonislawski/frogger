#include <WinRect.h>
#include <Game.h>

extern Game * game;

WinRect::WinRect(): QObject(), QGraphicsRectItem(){
    this->setRect(0,0,98,98);
    this->setBrush(Qt::green);

    while (getPosition() % 100) {
        setPosition(rand() % 1500);
    }
    this->setPos(getPosition(), 0);
    game->winPointsArr.append(this->position);
}

void WinRect::checkCollision() {
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n;  ++i) {
        if (colliding_items[i]->flags().testFlag(ItemIsFocusable)) {
            game->runNextLevel();
        } else if (colliding_items[i]->flags().testFlag(ItemIsPanel)) {
        } else {
            srand ( (unsigned)time(NULL) );
            int randomPosition = rand() % 1500;
            this->setPos(randomPosition, 0);
        }
    }
}

void WinRect::setPosition(int position) {
   this->position = position;
}

int WinRect::getPosition() {
   return this->position;
}
