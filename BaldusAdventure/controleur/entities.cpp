#include "entities.h"




Entities::Entities(int aX, int aY, QRect *aShape, QObject *parent)
    : QObject(parent), itsX(aX), itsY(aY), itsShape(aShape)
{}

Entities::~Entities()
{
    delete itsShape;
}


int Entities::getItsX() const
{
    return itsX;
}

void Entities::setItsX(int newItsX)
{
    itsX = newItsX;
}

int Entities::getItsY() const
{
    return itsY;
}

void Entities::setItsY(int newItsY)
{
    itsY = newItsY;
}

QRect *Entities::getItsShape() const
{
    return itsShape;
}

void Entities::setItsShape(QRect *newItsShape)
{
    itsShape = newItsShape;
}

std::list<QPixmap> *Entities::getItsPixMap() const
{
    return itsPixMap;
}

void Entities::setItsPixMap(std::list<QPixmap> *newItsPixMap)
{
    itsPixMap = newItsPixMap;
}
