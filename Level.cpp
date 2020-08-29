#include "Level.h"
#include <QFont>

Level::Level(QGraphicsItem *parent): QGraphicsTextItem(parent){
    resetLevel();

    // draw the text
    setPlainText(QString("Score: ") + QString::number(level));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

void Level::increase(){
    level++;
    setPlainText(QString("Score: ") + QString::number(level));
}

int Level::getLevel(){
    return level;
}

void Level::resetLevel() {
    level = 1;
}
