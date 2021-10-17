#define MAP_1 "../StonerIt/BD/map1.txt"
#define MAP_3 "../StonerIt/BD/map3.txt"
#define MAP_CHIEF "../StonerIt/BD/mapJefe.txt"

#include "sonerit.h"
#include "ui_sonerit.h"

sonerit::sonerit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sonerit)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    map map1(MAP_1,scene,&blocksVector),map3(MAP_3,scene2,&blocksVector),mapChief(MAP_CHIEF,scene3,&blocksVector);

    hero Hero;
    enemy Enemy;
    //h = scene->addRect(0,0,30,30,*Hero.border,*Hero.shapeBrush);
    //e = scene->addRect(0,0,40,40,*Enemy.border,*Enemy.shapeBrush);
    //e->setPos(100,100);
    //h->setFlag(QGraphicsItem::ItemIsMovable,true);

    ui->graphicsView->setSceneRect(0,0,1250,1000);

    //QTimer* timerMov = new QTimer(this);
    //connect(timerMov,SIGNAL(timeout()),this,SLOT(move()));
    //timerMov->start(100);

    //QTimer* timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(enemyShoot()));
    //timer->start(1000);
}

sonerit::~sonerit()
{
    delete ui;
}

void sonerit::move(){
    h->setPos(hXPOS,hYPOS);
}

void sonerit::enemyShoot(){
    e->setPos(e->x(),e->y()-20);
    bullet = scene->addEllipse(0,0,10,10,QPen(Qt::black),Qt::blue);
    bullet->setPos(e->x(),e->y());
    timerM  =new QTimer(this);
    connect(timerM,SIGNAL(timeout()),this,SLOT(moveBullet()));
    timerM->start(10);

}

void sonerit::moveBullet(){
    const int movSpeed = 1;
    if(bullet->x()<=e->x()-99||bullet->collidesWithItem(h)){
        if(bullet->collidesWithItem(h)){
            scene->addRect(bullet->x(),bullet->y(),10,10,QPen(Qt::red),Qt::red);
        }
        scene->removeItem(bullet);
        timerM->stop();
    }
    else if(!bullet->collidesWithItem(h)) bullet->setPos(bullet->x()-movSpeed,bullet->y());
}

void sonerit::keyPressEvent(QKeyEvent *event){
    int movingSpace = 7;
    switch (event->key()) {
    case Qt::Key_A:{
        hXPOS-=movingSpace;
    }
        break;
    case Qt::Key_W:{
        hYPOS-=movingSpace;
    }
        break;
    case Qt::Key_D:{
        hXPOS+=movingSpace;
    }
        break;
    case Qt::Key_S:{
        hYPOS+=movingSpace;
    }
        break;
    case Qt::Key_3:{
        ui->graphicsView->setScene(scene2);
    }
        break;
    case Qt::Key_J:{
        ui->graphicsView->setScene(scene3);
    }
        break;
    }
}
