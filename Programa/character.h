#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsRectItem>
#include <QImage>

class character
{
public:
    int getHealth();
    int getDamage();
    int size;
    int health;
    /*classtype*/ int power;
    int powerDamage;
    int powerDistance;
    int movementSpeed;

    QGraphicsRectItem* shape;
    QImage charImg;
};

#endif // CHARACTER_H
