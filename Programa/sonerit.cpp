#define MAP_1 "../StonerIt/BD/map1/"
#define MAP_2 "../StonerIt/BD/map2/"
#define MAP_3 "../StonerIt/BD/map3/"
#define MAP_4 "../StonerIt/BD/map4/"
#define MAP_5 "../StonerIt/BD/map5/"

#include "sonerit.h"
#include "ui_sonerit.h"

sonerit::sonerit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sonerit)
{
    ui->setupUi(this);

    start = new QGraphicsScene(this);
    start->setBackgroundBrush(Qt::blue);
    ui->graphicsView->setScene(start);
    activeScene = 0;

    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);
    scene5 = new QGraphicsScene(this);


    map map1(MAP_1,scene1,&blocksVector,&enemies),
        map2(MAP_2,scene2,&blocksVector2,&enemies2),
        map3(MAP_3,scene3,&blocksVector3,&enemies3),
        map4(MAP_4,scene4,&blocksVector4,&enemies4),
        map5(MAP_5,scene5,&blocksVector5,&enemies5);

    hero Hero;
    enemy enemy1(100,20,7),
          enemy2(200,30,5),
          enemy3(125,25,9),
          enemy4(200,40,9),
          enemy5(300,50,11);

    h = ui->graphicsView->scene()->addRect(hXPOS,hYPOS,30,30,*Hero.border,*Hero.shapeBrush);
    ui->graphicsView->setSceneRect(0,0,1250,1000);

    QTimer* timerMov = new QTimer(this);
    connect(timerMov,SIGNAL(timeout()),this,SLOT(move()));
    timerMov->start(1);

    /*QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(enemyShoot()));
    timer->start(5000);*/
}

sonerit::~sonerit()
{
    delete ui;
}

void sonerit::changeScene()
{
    switch (activeScene){
        case 0:{
            ui->graphicsView->setScene(scene1);
            activeScene = 1;
        }
            break;
            break;
        case 1:{
            ui->graphicsView->setScene(scene2);
            activeScene = 2;
        }
            break;
        case 2:{
            ui->graphicsView->setScene(scene3);
            activeScene = 3;
        }
            break;
        case 3:{
            ui->graphicsView->setScene(scene4);
            activeScene = 4;
        }
            break;
        case 4:{
            ui->graphicsView->setScene(scene5);
            activeScene = 5;
        }
            break;
        case 5:{
            ui->graphicsView->setScene(end);
            activeScene = 6;
        }
            break;
    }
}

void sonerit::move(){
    h->setPos(hXPOS,hYPOS);
    if(detectCollision(h)) changeScene();
    //int i=0;
    /*for(auto ene:enemies){
        ene->setPos(eXPOS,eYPOS+(i*50));
        if(detectCollision(ene)){
            if(enemyMovConst>0){
                int j=0;
                for(auto enm:enemies){
                    enm->setPos(eXPOS,549+(i*100));
                    j++;}
            }
            else if(enemyMovConst<0){
                int j=0;
                for(auto enm:enemies){
                    enm->setPos(eXPOS,51+(i*50));
                    j++;}
            }
            enemyMovConst= -(enemyMovConst);
        }
        i++;
    }*/

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
                    ui->graphicsView->scene()->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::red);
                }
                ui->graphicsView->scene()->removeItem(bull);
                if(bull->collidesWithItem(h)||detectCollision(bull)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        if(bullets.at(ind)==bull){
                            bullets.erase(bullets.cbegin()+ind);
                            if(bullets.size()==0) timerM->stop();
                            break;
                        }
                    }
                }
                if((bull->x())<=(500)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        ui->graphicsView->scene()->removeItem(bullets.at(ind));
                    }
                    bullets.clear();
                    timerM->stop();
                }
            }
            else bull->setPos(bull->x()-movSpeed,bull->y());
        }
}

void sonerit::keyPressEvent(QKeyEvent *event){
    int movingSpace = 7;
    if(event->key()==Qt::Key_Space&&(heroBullets.size()==0)) createHeroBullet();
    switch (event->key()) {
    case Qt::Key_A:{
        hXPOS-=movingSpace;
        if(detectCollision(h)){
            hXPOS+=2*movingSpace;
        }
    }
        break;
    case Qt::Key_W:{
        hYPOS-=movingSpace;
        if(detectCollision(h)) hYPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_D:{
        hXPOS+=movingSpace;
        if(detectCollision(h)) hXPOS-=2*movingSpace;
    }
        break;
    case Qt::Key_S:{
        hYPOS+=movingSpace;
        //changeScene();
        if(detectCollision(h)) hYPOS-=2*movingSpace;

    }
        break;
    case Qt::Key_J:{
        changeScene();
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

bool sonerit::bullCollToEnm(){
    for(auto bull:heroBullets){
        for(auto enm:enemies){
            if(bull->collidesWithItem(enm)) return true;
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

void sonerit::createHeroBullet()
{
    qreal x=h->x(), y=h->y()+15;
    QGraphicsItem* temp = ui->graphicsView->scene()->addEllipse(0,0,10,10,QPen(Qt::transparent),Qt::yellow);
    temp->setPos(x,y);
    heroBullets.push_front(temp);
    //if(timerHB->isActive()) timerHB->stop();
    timerHB = new QTimer(this);
    connect(timerHB,SIGNAL(timeout()),this,SLOT(moveHeroBullets()));
    timerHB->start(50);
}

void sonerit::moveHeroBullets()
{
    const int movSpeed = 7;
        for(auto bull:heroBullets){
            if(bullCollToEnm()||detectCollision(bull)||(bull->x())>=(1100)){
                if(bullCollToEnm()){
                    ui->graphicsView->scene()->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::green);
                }
                ui->graphicsView->scene()->removeItem(bull);
                if(bullCollToEnm()||detectCollision(bull)){
                    std::list<QGraphicsItem*>::iterator it;
                    for (auto itr = heroBullets.begin();itr != heroBullets.end(); itr++) {
                            if(*itr==bull){
                                it=itr;
                                heroBullets.erase(it);
                                break;
                            }
                     }
                }
                if((bull->x())>=(1100)){
                    heroBullets.pop_back();
                    timerHB->stop();
                }
            }
            else bull->setPos(bull->x()+movSpeed,bull->y());
        }
}

void sonerit::on_continue_button_clicked()
{

}


