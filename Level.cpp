#include "Level.h"
#include <QFont>

Level::Level(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    level = 0;

    // draw the text
    setPlainText(QString("Score: ") + QString::number(level)); // Score: 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Level::increase(){
    level++;
    setPlainText(QString("Level: ") + QString::number(level)); // Score: 1
}

int Level::getLevel(){
    return level;
}
