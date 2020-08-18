#ifndef WINRECT_H
#define WINRECT_H

#include <QGraphicsRectItem>
#include <QObject>

class WinRect:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WinRect();
public slots:
    void checkCollision();
};

#endif // WINRECT_H
