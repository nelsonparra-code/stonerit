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
    void clear();


    void changeScene();
protected slots:
    void move();
    void enemyShoot();
    void moveBullet();

protected:
    QGraphicsScene* scene;
    QGraphicsScene* scene2;
    QGraphicsScene* scene3;
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::sonerit *ui;

    QTimer* timerM;

    qreal hXPOS=0, hYPOS=0;

    QGraphicsItem* h;
    QGraphicsItem* e;
    QGraphicsItem* bullet;

    std::vector<QGraphicsRectItem*> blocksVector;

};
#endif // SONERIT_H
