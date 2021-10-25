#include "enemy.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

enemy::enemy(int _health, int _damage, int _movSpeed)
{
    health = _health;
    powerDamage = _damage;
    movementSpeed = _movSpeed;
}
enemy::enemy(int _health, int _damage, float _vx, float _vy)
{
    health = _health;
    powerDamage = _damage;
    vx = _vx;
    vxo = _vx;
    vy = _vy;
}
enemy::enemy(int _health, int _damage, float _vx, float _vy, float _a)
{
    health = _health;
    powerDamage = _damage;
    vx = _vx;
    vxo = _vx;
    vy = _vy;
    a = _a;
}
enemy::enemy(QString s, int _size)
{
    charImg = QImage(s);
    shapeBrush = new QBrush(charImg.scaled(_size,_size,Qt::KeepAspectRatio));
}

void enemy::moveEnemies1(std::vector<QGraphicsRectItem*> enems, std::vector<QGraphicsRectItem*> vctr,int* movConst,qreal* posY)
{
    for(auto enm:enems){
        float t = 0.1;
        float y = enm->y()+(vy*t);
        enm->setPos(enm->x(),y);
        if(y>=870){
            vy=-vy;
        }
        else if(y<=55){
            vy=-vy;
        }
    }
    /*int i=1;
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
    }*/
}

void enemy::moveEnemie2(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){
        float t = 0.1;
        //movement enemyMov(1100,enm->x(),enm->y(),vxo,vx,vy);
        float y = enm->y()+(vy*t);
        float x = enm->x()+(vx*t)+(9.81*t*t)/2.0;
        vx += 9.81*t;
        if(x>=1100){
            vx=vxo;
            vy=-vy;
        }
        /*enemyMov.calcParabPos(0.1);
        vx = enemyMov.getVx(), vy = enemyMov.getVy();
        enm->setPos(enemyMov.getPx(),enemyMov.getPy());*/
        enm->setPos(x,y);
    }
}

void enemy::moveEnemies3(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){
        float t = 0.1;
        float y = enm->y()+(vy*t);
        enm->setPos(enm->x(),y);
        if(y>=870){
            vy=-vy;
        }
        else if(y<=55){
            vy=-vy;
        }
    }
    /*for(auto enm:enems){
        float t = 0.1;
        movement enemyMov(enm->x(),enm->x(),enm->y(),vxo,vx,vy,a);
        enemyMov.calcCircPos(0.1);
        vx = enemyMov.getVx(), vy = enemyMov.getVy();
        enm->setPos(enemyMov.getPx(),enemyMov.getPy());
        float x = enm->x(), y = enm->y();
        float ax = a*cos(atan2(y,x)),
                ay = a*sin(atan2(y,x));
        y += (vy*t)+(ay*t*t)/2.0;
        x += (vx*t)+(ax*t*t)/2.0;
        vx += ax*t;
        vy += ay*t;
        enm->setPos(x,y);
    }*/
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
