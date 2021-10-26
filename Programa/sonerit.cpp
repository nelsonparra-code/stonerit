
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
    for(auto e:enemies4){
        e->setPos(1000,500);
    }

    timerMov = new QTimer(this);
    connect(timerMov,SIGNAL(timeout()),this,SLOT(move()));

    timerLive = new QTimer(this);
    connect(timerLive,SIGNAL(timeout()),this,SLOT(checkStatus()));

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
            createHero();
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies.size();h++){
                enemiesHealth.push_back(enemy1.getHealth());
            }
            activeScene = 1;
        }
            break;
        case 1:{
            ui->graphicsView->setScene(scene2);
            createHero();
            activeScene = 2;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies2.size();h++){
                enemiesHealth.push_back(enemy2.getHealth());
            }
        }
            break;
        case 2:{
            ui->graphicsView->setScene(scene3);
            createHero();
            activeScene = 3;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies3.size();h++){
                enemiesHealth.push_back(enemy3.getHealth());
            }
        }
            break;
        case 3:{
            ui->graphicsView->setScene(scene4);
            createHero();
            activeScene = 4;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies4.size();h++){
                enemiesHealth.push_back(enemy4.getHealth());
            }
        }
            break;
        case 4:{
            ui->graphicsView->setScene(scene5);
            createHero();
            activeScene = 5;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies5.size();h++){
                enemiesHealth.push_back(enemy5.getHealth());
            }
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
    heroS->setPos(h1XPOS,h1YPOS);
    if(secondHeroExists){
        h2->setPos(h2XPOS,h2YPOS);
        heroS2->setPos(h2XPOS,h2YPOS);
    }
    if(activeScene==1) enemy1.moveEnemies1(enemies,blocksVector,&enemyMovConst,&eYPOS);
    if(activeScene==2) enemy2.moveEnemie2(enemies2);
    if(activeScene==3) enemy3.moveEnemies3(enemies3);
    if(activeScene==4) enemy4.moveEnemie4(enemies4);

}

void sonerit::enemyShoot(){
    //eYPOS+=enemyMovConst;
    for(auto enm:enemies){
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
    if(event->key()==Qt::Key_E&&(heroBullets.size()==0)) createHeroBullet(h1);
    switch (event->key()) {
    case Qt::Key_A:{
        h1XPOS-=movingSpace;
        heroS->changeDirection(210);
        if(detectCollision(h1)) h1XPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_W:{
        h1YPOS-=movingSpace;
        heroS->changeDirection(140);
        if(detectCollision(h1)) h1YPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_D:{
        h1XPOS+=movingSpace;
        heroS->changeDirection(70);
        if(detectCollision(h1)) h1XPOS-=2*movingSpace;

    }
        break;
    case Qt::Key_S:{
        h1YPOS+=movingSpace;
        heroS->changeDirection(0);
        if(detectCollision(h1)) h1YPOS-=2*movingSpace;

    }
        break;
    case Qt::Key_H:{
        h2XPOS-=movingSpace;
        heroS2->changeDirection(210);
        if(detectCollision(h2)) h2XPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_U:{
        h2YPOS-=movingSpace;
        heroS2->changeDirection(140);
        if(detectCollision(h2)) h2YPOS+=2*movingSpace;
    }
        break;
    case Qt::Key_K:{
        h2XPOS+=movingSpace;
        heroS2->changeDirection(70);
        if(detectCollision(h2)) h2XPOS-=2*movingSpace;
    }
        break;
    case Qt::Key_J:{
        h2YPOS+=movingSpace;
        heroS2->changeDirection(0);
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
        for(auto block:blocksVector3){
            if(object->collidesWithItem(block)){
                return true;
            }
        }
    }
    return false;
}

bool sonerit::bullCollToEnm(){
    int i=0;
    for(auto bull:heroBullets){
        if(activeScene==1){
            for(auto enm:enemies){
                if(bull->collidesWithItem(enm)){
                    enemiesHealth[i] -= Hero.getDamage();
                    std::cout<<enemiesHealth[i]<<std::endl;
                    return true;
                }
                i++;
            }
        }
        else if(activeScene==2){
            for(auto enm:enemies2){
                if(bull->collidesWithItem(enm)){
                    enemiesHealth[i] -= Hero.getDamage();
                    std::cout<<enemiesHealth[i]<<std::endl;
                    return true;
                }
                i++;
            }
        }
        else if(activeScene==3){
            for(auto enm:enemies3){
                if(bull->collidesWithItem(enm)){
                    enemiesHealth[i] -= Hero.getDamage();
                    std::cout<<enemiesHealth[i]<<std::endl;
                    return true;
                }
                i++;
            }
        }
        else if(activeScene==4){
            for(auto enm:enemies4){
                if(bull->collidesWithItem(enm)){
                    enemiesHealth[i] -= Hero.getDamage();
                    std::cout<<enemiesHealth[i]<<std::endl;
                    return true;
                }
                i++;
            }
        }
        else{
            for(auto enm:enemies5){
                if(bull->collidesWithItem(enm)){
                    enemiesHealth[i] -= Hero.getDamage();
                    std::cout<<enemiesHealth[i]<<std::endl;
                    return true;
                }
                i++;
            }
        }
    }
    return false;
}

void sonerit::on_pushButton_clicked()
{
    if(ui->checkBox->checkState()==Qt::Checked) secondHeroExists = true;
    changeScene();

    timerMov->start(10);
    timerLive->start(15);
    timer->start(5000);

    ui->continue_button->~QPushButton();
    ui->pushButton->~QPushButton();
    ui->label->~QLabel();
    ui->checkBox->~QCheckBox();
}

void sonerit::createHeroBullet(QGraphicsItem* hr)
{
    timerMov->stop();
    timerMov->start(10);
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
    const int movSpeed = 15;
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
                                timerHB->stop();
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

void sonerit::createHero(){
    h1XPOS=h1XPOS_O, h1YPOS=h1YPOS_O,h2XPOS=h2XPOS_O, h2YPOS=h2YPOS_O;
    h1 = ui->graphicsView->scene()->addRect(0,0,70,70,QPen(Qt::black),Qt::transparent);
    h1->setPos(h1XPOS,h1YPOS);
    heroS = new sprite();
    ui->graphicsView->scene()->addItem(heroS);
    heroS->setPos(h1XPOS,h1YPOS);
    if(secondHeroExists){
        h2 = ui->graphicsView->scene()->addRect(0,0,70,70,QPen(Qt::red),Qt::transparent);
        h2->setPos(h2XPOS,h2YPOS);
        heroS2 = new sprite();
        ui->graphicsView->scene()->addItem(heroS2);
        heroS2->setPos(h2XPOS,h2YPOS);
    }
}

void sonerit::checkStatus(){
    for(unsigned long long x=0;x<enemiesHealth.size();x++){
        if(enemiesHealth[x]>0) break;
        if(x==(enemiesHealth.size()-1)) changeScene();
    }
}
