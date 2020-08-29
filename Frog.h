#ifndef Frog_H
#define Frog_H

#include <QGraphicsRectItem>
#include <QObject>

class Frog:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Frog(int viewWidth, int viewHeight);
    void keyPressEvent(QKeyEvent * event);
};

#endif // Frog_H
