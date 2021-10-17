#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <fstream>
#include <QGraphicsScene>

class map
{
public:
    map(std::string,QGraphicsScene*,std::vector<QGraphicsRectItem*>*);

    std::vector<std::vector<int> > getValue() const;
    int blockSize = 50;

private:
    std::vector<std::vector<int>> value;
};

#endif // MAP_H
