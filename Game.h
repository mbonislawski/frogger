#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>

class Game: public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    void displayMainMenu();
    void runNextLevel();
    void showCounter();
    void showLevel();
    void spawnFrog();
    void displayGameOverWindow(QString textToDisplay);

    QGraphicsScene * scene;
    int viewWidth;
    int viewHeight;
    int level;
    int lastCarPos = 0;
    int lastCarType = 0;
    QVector<int> winPointsArr;
    int timerVal;
    QMetaObject::Connection spawnConnection;
    QMetaObject::Connection startCountConnection;
    int startCounter = 6;
    QGraphicsTextItem* counterText;

public slots:
    void spawnCar();
    void restartGame();
    void start();
    void countStart();

private:
    void increaseLevel();
    void resetLevel();
    void drawPanel(int x, int y, int width, int height, QColor color);
};

#endif // GAME_H
