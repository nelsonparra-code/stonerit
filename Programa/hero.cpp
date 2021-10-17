#include "hero.h"

hero::hero(/*QObject *parent) : QObject(parent*/)
{
    health = 500;

    powerDamage = 75;
    powerDistance = 500;

    charImg = new QImage("../usuario/");
    border = new QPen(Qt::black);
    //QBrush shapeBrush(*charImg);
    shapeBrush = new QBrush(Qt::blue);
}
