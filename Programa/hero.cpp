#include "hero.h"

hero::hero(int _health, int _damage, int _moveSp, QString s)
{
    health = _health;
    powerDamage = _damage;
    movementSpeed = _moveSp;

    QImage img(s);
    brush = QBrush(img.scaled(10,10,Qt::KeepAspectRatio));
}

QBrush hero::getBrush() const
{
    return brush;
}
