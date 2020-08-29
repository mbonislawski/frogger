#ifndef WINRECT_H
#define WINRECT_H

#include <QGraphicsRectItem>
#include <QObject>

class WinRect:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WinRect();
private:
    int position;
    int getPosition();
    void setPosition(int position);
public slots:
    void checkCollision();
};

#endif // WINRECT_H
