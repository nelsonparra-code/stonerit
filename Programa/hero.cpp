#include "hero.h"

hero::hero(int _health, int _damage, int _moveSp, std::string str/*QObject *parent) : QObject(parent*/)
{
    health = _health;

    powerDamage = _damage;
    movementSpeed = _moveSp;

    QString qstr = QString::fromStdString(str+"h.png");

    charImg = QImage(qstr);
    border = new QPen(Qt::transparent);
    shapeBrush = new QBrush(charImg);
}
