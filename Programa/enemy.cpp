#include "enemy.h"
#include <QGraphicsRectItem>

enemy::enemy(int _health, int _damage, int _movSpeed/*QObject *parent) : QObject(parent*/)
{
    health = _health;

    powerDamage = _damage;
    movementSpeed = _movSpeed;
}
enemy::enemy(QString s/*QObject *parent) : QObject(parent*/)
{
    charImg = QImage(s);
    border = new QPen(Qt::transparent);
    shapeBrush = new QBrush(charImg);
}
