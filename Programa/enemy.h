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
    QBrush* shapeBrush;
    void moveEnemies1(std::vector<QGraphicsRectItem*>,std::vector<QGraphicsRectItem*>,int*,qreal*);
    void moveEnemie2();
    void moveEnemies3();
    void moveEnemie4();
    void moveEnemie5();
    bool detectCollision(QGraphicsItem*,std::vector<QGraphicsRectItem*>);

signals:

};

#endif // ENEMY_H
