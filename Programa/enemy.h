#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

#include <QObject>
#include <QPen>

class enemy : /*public QObject, */public character
{
    //Q_OBJECT
public:
    explicit enemy(int,int,int/*QObject *parent = nullptr*/);
    enemy(QString/*QObject *parent = nullptr*/);
    QPen* border;
    //QBrush shapeBrush(*charImg);
    QBrush* shapeBrush;

signals:

};

#endif // ENEMY_H
