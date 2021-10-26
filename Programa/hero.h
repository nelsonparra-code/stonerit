#ifndef HERO_H
#define HERO_H

#include "character.h"

#include <QObject>
#include <QPen>

class hero : public character
{
    //Q_OBJECT
public:
    explicit hero(int,int,int);
};

#endif // HERO_H
