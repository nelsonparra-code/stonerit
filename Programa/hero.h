#ifndef HERO_H
#define HERO_H

#include "character.h"

#include <QObject>
#include <QPen>

class hero : public character/*, public QObject*/
{
    //Q_OBJECT
public:
    explicit hero(/*QObject *parent = nullptr*/);
    QPen* border;
    //QBrush shapeBrush(*charImg);
    QBrush* shapeBrush;

signals:

};

#endif // HERO_H
