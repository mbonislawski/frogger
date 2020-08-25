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

    resetLevel();

    // create a scene
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
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
        if (winPointsArr.indexOf(i) == -1) {
            LoseRect * losePoint = new LoseRect(i);
            scene->addItem(losePoint);
            connect(timerCollision, SIGNAL(timeout()), losePoint, SLOT(checkCollision()));
        }
    }

    showLevel();

    // spawn enemies
    spawnConnection = connect(timer, SIGNAL(timeout()), this, SLOT(spawnCar()));
    timer->start(2000 / level);

    // check collision
    connect(timerCollision, SIGNAL(timeout()), winPoint1, SLOT(checkCollision()));
    connect(timerCollision, SIGNAL(timeout()), winPoint2, SLOT(checkCollision()));
    connect(timerCollision, SIGNAL(timeout()), winPoint3, SLOT(checkCollision()));

    timerCollision->start();

    show();
}

void Game::restartGame(){
    resetLevel();
    scene->clear();
    start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color){
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
    levelText->setDefaultTextColor(Qt::white);
    levelText->setFont(titleFont);
    int txPos = 20;
    int tyPos = 950;
    levelText->setPos(txPos,tyPos);
    scene->addItem(levelText);
}

void Game::displayGameOverWindow(QString textToDisplay){
    // disable all scene items
    scene->clear();
    QObject::disconnect(spawnConnection);

    // pop up semi transparent panel
    drawPanel(0,0, viewWidth, viewHeight, Qt::black);

    // create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(700,700);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));


    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(630,500);
    QFont textFont("comic sans",50);
    overText->setFont(textFont);
    scene->addItem(overText);
}

void Game::displayMainMenu(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Frogger Game"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    titleText->setPos(txPos, 500);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    playButton->setPos(bxPos, 650);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);
}

void Game::runNextLevel() {
    increaseLevel();
    scene->clear();
    start();
}

void Game::increaseLevel() {
    level = level + 1;
}

void Game::resetLevel() {
    level = 1;
}

void Game::spawnCar()
{
    Car * car = new Car();
    scene->addItem(car);
}

