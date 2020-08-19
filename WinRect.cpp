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
    this->setRect(0,0,98,98);
    this->setBrush(Qt::green);
//    this->setFlag(ItemIsPanel, true);
    while (this->position % 100) {
        this->position = rand() % 1500;
    }
    this->setPos(this->position, 0);
    game->winPointsArr.append(this->position);
}

void WinRect::checkCollision() {
    // if frog colides with the win point, start next level
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
