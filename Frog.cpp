#include <Frog.h>
#include <QKeyEvent>
#include <Car.h>
#include <QGraphicsView>
#include <Game.h>

extern Game * game;

Frog::Frog(int viewWidth, int viewHeight): QObject(), QGraphicsRectItem(){
    this->setRect(0,0,48,48);
    this->setBrush(Qt::green);
    this->setPos(viewWidth/2, (viewHeight - this->rect().height()) - 1);

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Frog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 0) {
            setPos(x()-25,y());
        }
    } else if (event->key() == Qt::Key_Right) {
        if (pos().x() + 25 < 1575) {
            setPos(x()+25, y());
        }
    } else if (event->key() == Qt::Key_Up) {
        if (pos().y() > 0) {
            setPos(x(), y()-25);
        }
    } else if (event->key() == Qt::Key_Down) {
        if (pos().y() + 25 < 975) {
            setPos(x(), y()+25);
        }
    }
}
