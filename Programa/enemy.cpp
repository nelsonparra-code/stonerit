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

void enemy::moveEnemies1(std::vector<QGraphicsRectItem*> enems, std::vector<QGraphicsRectItem*> vctr,int* movConst,qreal* posY)
{
    int i=1;
    for(auto ene:enems){
        ene->setPos(ene->x(),(*posY)+(i*100));
        if(detectCollision(ene,vctr)){
            if(*movConst>0){
                int j=0;
                for(auto enm:enems){
                    enm->setPos(enm->x(),440+(j*100));
                    j++;}
            }
            else if(*movConst<0){
                int j=0;
                for(auto enm:enems){
                    enm->setPos(enm->x(),50+(j*50));
                    j++;}
            }
            *movConst= -(*movConst);
            break;
        }
        i++;
    }
}

void enemy::moveEnemie2()
{

}

void enemy::moveEnemies3()
{

}

void enemy::moveEnemie4()
{

}

void enemy::moveEnemie5()
{

}

bool enemy::detectCollision(QGraphicsItem* object, std::vector<QGraphicsRectItem*> bVector){
    for(auto block:bVector){
        if(object->collidesWithItem(block)){
            return true;
        }
    }
    return false;
}
