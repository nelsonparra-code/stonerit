
#define MAP_1 "../StonerIt/BD/map1/"
#define MAP_2 "../StonerIt/BD/map2/"
#define MAP_3 "../StonerIt/BD/map3/"
#define MAP_4 "../StonerIt/BD/map4/"
#define MAP_5 "../StonerIt/BD/map5/"
#define DATA "../StonerIt/BD/data.txt"

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

    std::ifstream inFile;
    inFile.open(DATA);

    std::string data;
    inFile >> data;

    std::string temp="";
    for(unsigned long long i=0;i<=data.length();i++){
        if(data[i]!=','&&data[i]!=';') temp+=data[i];
        else if(data[i]==','||data[i]==';'){
            gameInfo.push_back(temp);
            temp="";
        }
    }
    inFile.close();

    if(gameInfo.size()==4 || gameInfo.size()==6) ui->continue_button->setDisabled(false);
    else ui->continue_button->setDisabled(true);

    map map1(MAP_1,scene1,&blocksVector,&enemies,70),
        map2(MAP_2,scene2,&blocksVectorChief,&enemies2,100),
        map3(MAP_3,scene3,&blocksVector3,&enemies3,70),
        map4(MAP_4,scene4,&enemies4,150),
        map5(MAP_5,scene5,&enemies5,200);

    ui->graphicsView->setSceneRect(0,0,1250,1000);

    for(auto e:enemies2){
        e->setPos(1100,300);
    }
    for(auto e:enemies4){
        e->setPos(1000,500);
    }

    checkStart = new QTimer(this);
    connect(checkStart,SIGNAL(timeout()),this,SLOT(checkScndPly()));
    checkStart->start(1);

    timerEnemyMov = new QTimer(this);
    connect(timerEnemyMov,SIGNAL(timeout()),this,SLOT(moveEnemies()));

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
            saveGame();
            ui->graphicsView->setScene(scene1);
            createHero();
            activeEnemies = enemies;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies.size();h++){
                enemiesHealth.push_back(enemy1.getHealth());
            }
            activeScene = 1;
        }
            break;
        case 1:{
            saveGame();
            ui->graphicsView->setScene(scene2);
            createHero();
            activeEnemies = enemies2;
            activeScene = 2;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies2.size();h++){
                enemiesHealth.push_back(enemy2.getHealth());
            }
        }
            break;
        case 2:{
            saveGame();
            ui->graphicsView->setScene(scene3);
            createHero();
            activeEnemies = enemies3;
            activeScene = 3;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies3.size();h++){
                enemiesHealth.push_back(enemy3.getHealth());
            }
        }
            break;
        case 3:{
            saveGame();
            ui->graphicsView->setScene(scene4);
            createHero();
            activeEnemies = enemies4;
            activeScene = 4;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies4.size();h++){
                enemiesHealth.push_back(enemy4.getHealth());
            }
        }
            break;
        case 4:{
            saveGame();
            ui->graphicsView->setScene(scene5);
            createHero();
            activeEnemies = enemies5;
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

}

void sonerit::moveEnemies(){
    if(activeScene==1) enemy1.moveEnemies1(enemies,blocksVector,&enemyMovConst,&eYPOS);
    if(activeScene==2) enemy2.moveEnemie2(enemies2);
    if(activeScene==3) enemy3.moveEnemies3(enemies3);
    if(activeScene==4) enemy4.moveEnemie4(enemies4);
    if(activeScene==5) enemy5.moveEnemie5(enemies5);

}

void sonerit::enemyShoot(){
    for(auto enm:activeEnemies){
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
    if(secondHeroExists){
        for(auto bull:bullets){
            if(bull->collidesWithItem(h1)||bull->collidesWithItem(h2)||detectCollision(bull)||(bull->x())<=(100)){
                if(bull->collidesWithItem(h1)){
                    ui->graphicsView->scene()->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::red);
                    heroHealth1-=enmArray[activeScene-1].getDamage();
                }
                if(bull->collidesWithItem(h2)){
                    ui->graphicsView->scene()->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::red);
                    heroHealth2-=enmArray[activeScene-1].getDamage();
                }
                ui->graphicsView->scene()->removeItem(bull);
                if(bull->collidesWithItem(h1)||bull->collidesWithItem(h2)||detectCollision(bull)){
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
    else{
        for(auto bull:bullets){
            if(bull->collidesWithItem(h1)||detectCollision(bull)||(bull->x())<=(100)){
                if(bull->collidesWithItem(h1)){
                    ui->graphicsView->scene()->addRect(bull->x(),bull->y(),10,10,QPen(Qt::red),Qt::red);
                    heroHealth1-=enmArray[activeScene-1].getDamage();
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
        for(auto enm:activeEnemies){
            if(bull->collidesWithItem(enm)){

                enemiesHealth[i] -= Hero.getDamage();
                if(enemiesHealth[i]<=0) ui->graphicsView->scene()->removeItem(activeEnemies.at(i));
                std::cout<<enemiesHealth[i]<<std::endl;
                return true;
            }
            i++;
        }
    }
    return false;
}

void sonerit::on_pushButton_clicked()
{
    ui->label_player1_name->setText(ui->textEdit_player1->toPlainText()+" Health:");
    if(ui->checkBox->checkState()==Qt::Checked){
        secondHeroExists = true;
        ui->label_player2_name->setText(ui->textEdit_player2->toPlainText()+" Health:");
    }

    heroHealth1 = Hero.getHealth();
    heroHealth2 = Hero.getHealth();

    changeScene();

    startGameTimers();

    ui->continue_button->~QPushButton();
    ui->pushButton->~QPushButton();
    ui->checkBox->~QCheckBox();
    checkStart->~QTimer();
}

void sonerit::createHeroBullet(QGraphicsItem* hr)
{
    timerMov->stop();
    timerMov->start(10);
    qreal x=hr->x()+70, y=hr->y()+35;
    QGraphicsItem* temp = ui->graphicsView->scene()->addRect(0,0,10,10,QPen(Qt::transparent),Hero.getBrush());
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
    loadGame();
    checkStart->~QTimer();
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
        if(x==(enemiesHealth.size()-1)){
            changeScene();
        }
    }
    ui->lcd_health1->display(heroHealth1);
    if(secondHeroExists) ui->lcd_health2->display(heroHealth2);
}

void sonerit::checkScndPly()
{
    if(ui->checkBox->isChecked()) ui->textEdit_player2->setDisabled(false);
    else ui->textEdit_player2->setDisabled(true);
}

void sonerit::loadGame()
{
    if(gameInfo.size()==6){
        playerName1 = gameInfo.at(0);
        playerName2 = gameInfo.at(1);
        activeScene = stoi(gameInfo.at(2));
        heroHealth1 = stoi(gameInfo.at(3));
        heroHealth2 = stoi(gameInfo.at(4));
        points = stoi(gameInfo.at(3));
        secondHeroExists = true;
        changeScene();
        startGameTimers();
    }
    else if(gameInfo.size()==4){
        playerName1 = gameInfo.at(0);
        activeScene = stoi(gameInfo.at(1));
        heroHealth1 = stoi(gameInfo.at(2));
        points = stoi(gameInfo.at(3));
        changeScene();
        startGameTimers();
    }
}

void sonerit::saveGame()
{
    std::string data;
    if(secondHeroExists){
        std::string data = playerName1+','+playerName2+','+std::to_string(activeScene)+
                ','+std::to_string(heroHealth1)+','+std::to_string(heroHealth2)+
                ','+std::to_string(points)+';';
    }
    else{
        std::string data = playerName1+','+std::to_string(activeScene)+
                ','+std::to_string(heroHealth1)+','+std::to_string(points)+';';
    }
    std::ofstream outFile;
    outFile.open(DATA);
    outFile << data;
    outFile.close();
}

void sonerit::startGameTimers()
{
    timerMov->start(10);
    timerEnemyMov->start(10);
    timerLive->start(15);
    timer->start(5000);

}
