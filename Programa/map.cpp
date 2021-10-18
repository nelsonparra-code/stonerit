#include "map.h"

map::map(std::string t, QGraphicsScene* s, std::vector<QGraphicsRectItem*>* v)
{
    QString qstrT = QString::fromStdString(t);
    std::vector<int> auxVctr {};
    QImage aBlock(qstrT+"a.png"), bBlock(qstrT+"b.png"), bg(qstrT+"bg.png");
    QBrush aBlockBrush(aBlock),bBlockBrush(bBlock),bgBrush(bg);
    s->setBackgroundBrush(bgBrush);

    std::ifstream inFile;
    inFile.open(t+"map.txt");

    std::string data;
    inFile >> data;

    for(unsigned long long i=0;i<data.length();i++){
        if(data[i]=='1'||data[i]=='0'||data[i]=='2') auxVctr.push_back(data[i]-48);
        else if(data[i]=='}'&&auxVctr.size()!=0){
            value.push_back(auxVctr);
            auxVctr.clear();
        }
    }
    inFile.close();

    int y=0;
    for(unsigned long long row=0;row<value.size();row++){
        int x=0;
        for(unsigned long long column=0;column<value.at(row).size();column++){
            if(value.at(row).at(column)==1){
                QGraphicsRectItem* temp = s->addRect(x,y,blockSize,blockSize,QPen(Qt::transparent),aBlockBrush);
                v->push_back(temp);
            }
            else if(value.at(row).at(column)==2){
                QGraphicsRectItem* temp = s->addRect(x,y,blockSize,blockSize,QPen(Qt::black),bBlockBrush);
                v->push_back(temp);
            }
            x+=blockSize;
        }
        y+=blockSize;
    }
}

std::vector<std::vector<int> > map::getValue() const
{
    return value;
}
