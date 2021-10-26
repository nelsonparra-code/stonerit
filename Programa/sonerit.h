#ifndef SONERIT_H
#define SONERIT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <hero.h>
#include "enemy.h"
#include "map.h"
#include "sprite.h"
#include <QTimer>
#include <QFlag>
#include <QKeyEvent>
#include <vector>
#include <list>

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class sonerit; }
QT_END_NAMESPACE

class sonerit : public QMainWindow
{
    Q_OBJECT

public:

    sprite *heroS;
    sprite *heroS2;

    sonerit(QWidget *parent = nullptr);
    ~sonerit();

    void changeScene();
    bool detectCollision(QGraphicsItem*);
    bool bullCollToEnm();
    bool secondHeroExists=false;
protected slots:
    void move();
    void enemyShoot();
    void moveBullet();

protected:
    QGraphicsScene* start;
    QGraphicsScene* scene1;
    QGraphicsScene* scene2;
    QGraphicsScene* scene3;
    QGraphicsScene* scene4;
    QGraphicsScene* scene5;
    QGraphicsScene* end;
    //std::vector<QGraphicsScene*> scenes{start,scene1,scene2,scene3,scene4,scene5,end};

    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_continue_button_clicked();
    void moveHeroBullets();
    void on_pushButton_clicked();
    void checkStatus();

private:
    Ui::sonerit *ui;

    QTimer* timer;
    QTimer* timerLive;
    QTimer* timerMov;
    QTimer* timerM;
    QTimer* timerHB;

    qreal h1XPOS_O=70, h1YPOS_O=70, h1XPOS=h1XPOS_O, h1YPOS=h1YPOS_O;
    qreal h2XPOS_O=70, h2YPOS_O=900, h2XPOS=h2XPOS_O, h2YPOS=h2YPOS_O;
    qreal eXPOS=1000,eYPOS=50;
    int enemyMovConst = 20;

    hero Hero = hero(500,20,7);
    QGraphicsItem* h1;
    QGraphicsItem* h2;
    QGraphicsItem* e;

    std::vector<int> enemiesHealth {};

    std::vector<QGraphicsRectItem*> enemies;
    std::vector<QGraphicsRectItem*> enemies2;
    std::vector<QGraphicsRectItem*> enemies3;
    std::vector<QGraphicsRectItem*> enemies4;
    std::vector<QGraphicsRectItem*> enemies5;

    std::vector<QGraphicsItem*> bullets;
    std::list<QGraphicsItem*> heroBullets;
    QGraphicsItem* bullet;
    void createHeroBullet(QGraphicsItem*);
    void createHero();

    int activeScene;
    std::vector<QGraphicsRectItem*> activeBlocks;
    std::vector<QGraphicsRectItem*> blocksVector;
    std::vector<QGraphicsRectItem*> blocksVectorChief;
    std::vector<QGraphicsRectItem*> blocksVector3;
    //std::vector<QGraphicsRectItem*> allBlocksVector[5] = {blocksVector,blocksVector2,blocksVector3,blocksVector4,blocksVector5};

    enemy enemy1 = enemy(100,20,0.0,7.0);
    enemy enemy2 = enemy(200,30,-62.64184,31.32096);
    enemy enemy3 = enemy(125,25,0.0,10.0);
    enemy enemy4 = enemy(200,40,0.0,-50.0,25.0);
    enemy enemy5 = enemy(300,50,11);

};
#endif // SONERIT_H
