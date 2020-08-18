#include <Frog.h>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QtDebug>
#include <Car.h>
#include <QTimer>
#include <QPainter>
#include <QGraphicsView>
#include <Game.h>

extern Game * game;

Frog::Frog(int viewWidth, int viewHeight): QObject(), QGraphicsRectItem(){
    this->setRect(0,0,100,100);
    this->setBrush(Qt::green);
    this->setPos(viewWidth/2,viewHeight - this->rect().height());

    // make rect focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Frog::keyPressEvent(QKeyEvent *event) {
//    qDebug() << "x: " << pos().x() << " y: " << pos().y();
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 0) {
            setPos(x()-100,y());
        }
    } else if (event->key() == Qt::Key_Right) {
        if (pos().x() + 100 < 1600) {
            setPos(x()+100, y());
        }
    } else if (event->key() == Qt::Key_Up) {
        if (pos().y() > 0) {
            setPos(x(), y()-150);
        }
    } else if (event->key() == Qt::Key_Down) {
        if (pos().y() + 100 < 1000) {
            setPos(x(), y()+150);
        }
    }
}

void Frog::spawnCar()
{
    // create an Car
    Car * car = new Car();
    scene()->addItem(car);
}
