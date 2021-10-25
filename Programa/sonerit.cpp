#define HERO "../StonerIt/BD/"
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


    map map1(MAP_1,scene1,&blocksVector,&enemies,70),
        map2(MAP_2,scene2,&blocksVectorChief,&enemies2,100),
        map3(MAP_3,scene3,&blocksVector3,&enemies3,70),
        map4(MAP_4,scene4,&blocksVectorChief,&enemies4,150),
        map5(MAP_5,scene5,&blocksVectorChief,&enemies5,200);

    ui->graphicsView->setSceneRect(0,0,1250,1000);

    for(auto e:enemies2){
        e->setPos(1100,300);
    }

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(enemyShoot()));
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
    h1->setPos(h1XPOS,h1YPOS);
    if(secondHeroExists) h2->setPos(h2XPOS,h2YPOS);
    if(activeScene==1) enemy1.moveEnemies1(enemies,blocksVector,&enemyMovConst,&eYPOS);
    if(activeScene==2){
        enemy2.moveEnemie2(enemies2);
    }
    if(activeScene==3){
        enemy3.moveEnemies3(enemies3);
    }

}

void sonerit::enemyShoot(){
    if(activeScene==1) enemy1.moveEnemies1(enemies,blocksVector,&enemyMovConst,&eYPOS);
    //if(activeScene==2) enemy2.moveEnemie2(enemies2,blocksVector2,&enemyMovConst,&eYPOS);
    eYPOS+=enemyMovConst;
    for(auto enm:enemies2){
        QGraphicsItem* temp = ui->graphicsView->scene()->addEllipse(0,0,10,10,QPen(Qt::black),Qt::yellow);
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
            if(bull->collidesWithItem(h1)||detectCollision(bull)||(bull->x())<=(100)){
                if(bull->collidesWithItem(h1)){
                    ui->graphicsView->scene()->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::red);
                }
                ui->graphicsView->scene()->removeItem(bull);
                if(bull->collidesWithItem(h1)||detectCollision(bull)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        if(bullets.at(ind)==bull){
                            bullets.erase(bullets.cbegin()+ind);
                            if(bullets.size()==0) timerM->stop();
                            break;
                        }
                    }
                }
                if((bull->x())<=(100)){
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
    //if(event->key()==Qt::Key_Space&&(heroBullets.size()==0)) createHeroBullet();
    switch (event->key()) {
    case Qt::Key_A:{
        h1XPOS-=movingSpace;
        if(detectCollision(h1)) h1XPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_W:{
        h1YPOS-=movingSpace;
        if(detectCollision(h1)) h1YPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_D:{
        h1XPOS+=movingSpace;
        if(detectCollision(h1)) h1XPOS-=2*movingSpace;
    }
        break;
    case Qt::Key_S:{
        h1YPOS+=movingSpace;
        if(detectCollision(h1)) h1YPOS-=2*movingSpace;

    }
        break;
    case Qt::Key_H:{
        h2XPOS-=movingSpace;
        if(detectCollision(h2)) h2XPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_U:{
        h2YPOS-=movingSpace;
        if(detectCollision(h2)) h2YPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_K:{
        h2XPOS+=movingSpace;
        if(detectCollision(h2)) h2XPOS-=2*movingSpace;
    }
        break;
    case Qt::Key_J:{
        h2YPOS+=movingSpace;
        if(detectCollision(h2)) h2YPOS-=2*movingSpace;

    }
        break;
    case Qt::Key_X:{
        changeScene();

    }
        break;
    }
}

bool sonerit::detectCollision(QGraphicsItem* object){
    if(activeScene==1){
        for(auto block:blocksVector){
            if(object->collidesWithItem(block)){
                return true;
            }
        }
    }
    else if(activeScene==2||activeScene==4||activeScene==5){
        for(auto block:blocksVectorChief){
            if(object->collidesWithItem(block)){
                return true;
            }
        }
    }
    else if(activeScene==3){
        for(auto block:blocksVector){
            if(object->collidesWithItem(block)){
                return true;
            }
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
    activeScene=2;
    changeScene();

    hero Hero(500,20,7,HERO);
    h1 = ui->graphicsView->scene()->addRect(0,0,30,30,*Hero.border,*Hero.shapeBrush);
    h1->setPos(h1XPOS,h1YPOS);
    QTimer* timerMov = new QTimer(this);
    connect(timerMov,SIGNAL(timeout()),this,SLOT(move()));
    timerMov->start(10);
    if(ui->checkBox->checkState()==Qt::Checked){
        hero Hero2(500,20,7,HERO);
        h2 = ui->graphicsView->scene()->addRect(0,0,30,30,QPen(Qt::yellow),*Hero2.shapeBrush);
        h2->setPos(h2XPOS,h2YPOS);
        secondHeroExists = true;
    }
    //timer->start(5000);

    ui->continue_button->~QPushButton();
    ui->pushButton->~QPushButton();
    ui->label->~QLabel();
    ui->checkBox->~QCheckBox();
}

void sonerit::createHeroBullet(QGraphicsItem* hr)
{
    qreal x=hr->x(), y=hr->y()+15;
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


