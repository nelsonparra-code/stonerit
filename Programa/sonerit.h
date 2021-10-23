#ifndef SONERIT_H
#define SONERIT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <hero.h>
#include <enemy.h>
#include "map.h"
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
    sonerit(QWidget *parent = nullptr);
    ~sonerit();

    void changeScene();
    bool detectCollision(QGraphicsItem*);
    bool bullCollToEnm();
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
    std::vector<QGraphicsScene*> scenes{start,scene1,scene2,scene3,scene4,scene5,end};

    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_continue_button_clicked();
    void moveHeroBullets();
    void on_pushButton_clicked();

private:
    Ui::sonerit *ui;

    QTimer* timerM;
    QTimer* timerHB;

    qreal hXPOS=60, hYPOS=60;
    qreal eXPOS=1000,eYPOS=60;
    int enemyMovConst = 20;

    QGraphicsItem* h;
    QGraphicsItem* e;
    std::vector<QGraphicsRectItem*> enemies;
    std::vector<QGraphicsRectItem*> enemies2;
    std::vector<QGraphicsRectItem*> enemies3;
    std::vector<QGraphicsRectItem*> enemies4;
    std::vector<QGraphicsRectItem*> enemies5;
    std::vector<QGraphicsItem*> bullets;
    std::list<QGraphicsItem*> heroBullets;
    QGraphicsItem* bullet;
    void createHeroBullet();

    int activeScene;
    std::vector<QGraphicsRectItem*> activeBlocks;
    std::vector<QGraphicsRectItem*> blocksVector;
    std::vector<QGraphicsRectItem*> blocksVector2;
    std::vector<QGraphicsRectItem*> blocksVector3;
    std::vector<QGraphicsRectItem*> blocksVector4;
    std::vector<QGraphicsRectItem*> blocksVector5;
    std::vector<std::vector<QGraphicsRectItem*>> allBlocksVector {blocksVector,blocksVector2,blocksVector3,blocksVector4,blocksVector5};

};
#endif // SONERIT_H
