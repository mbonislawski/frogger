#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include <Car.h>
#include <QDebug>
#include <QGraphicsView>
#include <Frog.h>
#include <WinRect.h>
#include <LoseRect.h>
#include "Button.h"
#include <QGraphicsTextItem>
#include <stdlib.h> // srand() and rand()
#include <time.h> // time()
#include <QFont>

Game::Game(QWidget *) {

    viewWidth = 1600;
    viewHeight = 1000;
    level = 1;

    // create a scene
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(0,0, viewWidth, viewHeight);

    // add a view
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    show();
}

void Game::start(){
    // clear the screen
    scene->clear();
    winPointsArr.remove(0, winPointsArr.size());

    // create a player
    Frog * frog = new Frog(this->viewWidth, this->viewHeight);
    scene->addItem(frog);

    WinRect * winPoint1 = new WinRect();
    scene->addItem(winPoint1);

    WinRect * winPoint2 = new WinRect();
    scene->addItem(winPoint2);

    WinRect * winPoint3 = new WinRect();
    scene->addItem(winPoint3);


    QTimer * timer = new QTimer();
    QTimer * timerCollision = new QTimer();

    for (int i = 0; i < 1600; i = i+100) {
        qDebug() << winPointsArr << " " << winPointsArr.indexOf(i) << " " << i;
        if (winPointsArr.indexOf(i) == -1) {
            LoseRect * losePoint = new LoseRect(i);
            scene->addItem(losePoint);
            connect(timerCollision, SIGNAL(timeout()), losePoint, SLOT(checkCollision()));
        }
    }

    showLevel();

    // spawn enemies
    connect(timer, SIGNAL(timeout()), frog, SLOT(spawnCar()));
    timer->start(2000 / level);

    // check collision
    connect(timerCollision, SIGNAL(timeout()), winPoint1, SLOT(checkCollision()));
    connect(timerCollision, SIGNAL(timeout()), winPoint2, SLOT(checkCollision()));
    connect(timerCollision, SIGNAL(timeout()), winPoint3, SLOT(checkCollision()));

    timerCollision->start();

    show();
}

void Game::restartGame(){
    level = 1;
    scene->clear();
    start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    scene->addItem(panel);
}

void Game::showLevel () {
    QGraphicsTextItem* levelText = new QGraphicsTextItem(QString("Level: ") +  QString::number(level));
    QFont titleFont("comic sans",20);
    levelText->setDefaultTextColor(Qt::black);
    levelText->setFont(titleFont);
    int txPos = 20;
    int tyPos = 950;
    levelText->setPos(txPos,tyPos);
    scene->addItem(levelText);
}

void Game::displayGameOverWindow(QString textToDisplay){
    // disable all scene items
    scene->clear();

    // pop up semi transparent panel
    drawPanel(0,0, viewWidth, viewHeight,Qt::black);

    // create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(700,700);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(750,500);
    scene->addItem(overText);

}

void Game::displayMainMenu(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Hex Warz"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);
}

void Game::runNextLevel() {
    this->level = this->level + 1;
    scene->clear();
    start();
}
