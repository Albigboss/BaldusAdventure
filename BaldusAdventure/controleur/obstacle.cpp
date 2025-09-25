#include "obstacle.h"
#include "QtGui/qpixmap.h"

ObstacleType Obstacle::getItsType() const
{
    return itsType;
}

Obstacle::Obstacle(int aX, int aY, ObstacleType aType, QRect* aShape, std::string aPixmapLink)
    : Entities(aX, aY, aShape), itsType(aType)
{
    std::list<QPixmap> *temp = new std::list<QPixmap>;
    temp->push_back(QPixmap(QString::fromStdString(aPixmapLink)));

    setItsPixMap(temp);
}
