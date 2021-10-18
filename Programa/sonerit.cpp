#define MAP_1 "../StonerIt/BD/map1/"
#define MAP_3 "../StonerIt/BD/map3/"
#define MAP_2 "../StonerIt/BD/map2/"

#include "sonerit.h"
#include "ui_sonerit.h"

sonerit::sonerit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sonerit)
{
    ui->setupUi(this);
    start = new QGraphicsScene(this);

    start->setBackgroundBrush(Qt::blue);

    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);
    scene5 = new QGraphicsScene(this);
    ui->graphicsView->setScene(start);
    map map1(MAP_1,scene1,&blocksVector),map3(MAP_3,scene2,&blocksVector),mapChief(MAP_2,scene3,&blocksVector);

    hero Hero;
    enemy Enemy;
    h = scene1->addRect(hXPOS,hYPOS,30,30,*Hero.border,*Hero.shapeBrush);
    for(int i=0;i<3;i++){
        QGraphicsItem* temp = scene1->addRect(0,0,40,40,*Enemy.border,*Enemy.shapeBrush);
        temp->setPos(eXPOS,eYPOS+(i*100));
        enemies.push_back(temp);
    }
    //e = scene->addRect(0,0,40,40,*Enemy.border,*Enemy.shapeBrush);
    //e->setPos(1000,60);
    h->setFlag(QGraphicsItem::ItemIsMovable,true);
    ui->graphicsView->setSceneRect(0,0,1250,1000);

    QTimer* timerMov = new QTimer(this);
    connect(timerMov,SIGNAL(timeout()),this,SLOT(move()));
    timerMov->start(100);

    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(enemyShoot()));
    timer->start(5000);
}

sonerit::~sonerit()
{
    delete ui;
}

void sonerit::changeScene()
{
    bool toActScene = false;
    for(auto sc:scenes){
        if(toActScene){
            ui->graphicsView->setScene(sc);
            break;
        }
        else{
            if(ui->graphicsView->scene()==sc) toActScene=true;
        }
    }
}

void sonerit::move(){
    h->setPos(hXPOS,hYPOS);
    if(detectCollision(h)) changeScene();
    int i=0;
    for(auto ene:enemies){
        ene->setPos(eXPOS,eYPOS+(i*50));
        if(detectCollision(ene)){
            if(enemyMovConst>0) ene->setPos(eXPOS,849+(i*50));
            else if(enemyMovConst<0) ene->setPos(eXPOS,51+(i*50));
            enemyMovConst= -(enemyMovConst);
        }
        i++;
    }

}

void sonerit::enemyShoot(){
    eYPOS+=enemyMovConst;
    for(auto enm:enemies){
        QGraphicsItem* temp = scene1->addEllipse(0,0,10,10,QPen(Qt::black),Qt::blue);
        temp->setPos(enm->x(),enm->y());
        bullets.push_back(temp);
    }
    timerM  = new QTimer(this);
    connect(timerM,SIGNAL(timeout()),this,SLOT(moveBullet()));
    timerM->start(50);

}

void sonerit::moveBullet(){
    const int movSpeed = 7;
    for(auto bull:bullets){
        if(bull->collidesWithItem(h)||detectCollision(bull)||(bull->x())<=(500)){
            if(bull->collidesWithItem(h)){
                scene1->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::red);
            }
            scene1->removeItem(bull);
            if(bull->collidesWithItem(h)||detectCollision(bull)){
                for(unsigned long long i=0;i<bullets.size();i++){
                    if(bullets.at(i)==bull){
                        bullets.erase(bullets.begin()+i);
                        break;
                    }
                }
            }
            else{
                bullets.clear();
                timerM->stop();
            }
        }
        else bull->setPos(bull->x()-movSpeed,bull->y());
    }
}

void sonerit::keyPressEvent(QKeyEvent *event){
    int movingSpace = 7;
    switch (event->key()) {
    case Qt::Key_A:{
        hXPOS-=movingSpace;
        //if(detectCollision(h)) hXPOS+=movingSpace;
    }
        break;
    case Qt::Key_W:{
        hYPOS-=movingSpace;
        //if(detectCollision(h)) hYPOS+=movingSpace;
    }
        break;
    case Qt::Key_D:{
        hXPOS+=movingSpace;
        //if(detectCollision(h)) hXPOS-=movingSpace;
    }
        break;
    case Qt::Key_S:{
        hYPOS+=movingSpace;
        //if(detectCollision(h)) hYPOS-=movingSpace;

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

bool sonerit::detectCollision(QGraphicsItem* object){
    for(auto block:blocksVector){
        if(object->collidesWithItem(block)){
            return true;
        }
    }
    return false;
}

void sonerit::on_pushButton_clicked()
{
    ui->continue_button->~QPushButton();
    ui->pushButton->~QPushButton();
    ui->label->~QLabel();
    ui->graphicsView->setScene(scene1);
}

void sonerit::on_continue_button_clicked()
{

}
