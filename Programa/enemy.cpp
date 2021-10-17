#include "enemy.h"
#include <QGraphicsRectItem>

enemy::enemy(/*QObject *parent) : QObject(parent*/)
{
    health = 250;

    powerDamage = 50;
    powerDistance = 500;

    charImg = new QImage("../usuario/");
    border = new QPen(Qt::black);
    //QBrush shapeBrush(*charImg);
    shapeBrush = new QBrush(Qt::red);
}
