#ifndef MAP_H
#define MAP_H

#include <QImage>
#include <string>
#include <vector>
#include <fstream>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "enemy.h"

class map
{
public:
    map(std::string,QGraphicsScene*,std::vector<QGraphicsRectItem*>*,std::vector<QGraphicsRectItem*>*,int);
    map(std::string,QGraphicsScene*,std::vector<QGraphicsRectItem*>*,int);

    std::vector<std::vector<int> > getValue() const;
    int blockSize = 50;

    QBrush bullet;

private:
    std::vector<std::vector<int>> value;
};

#endif // MAP_H
