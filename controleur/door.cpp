#include "door.h"
#include "QtCore/qdebug.h"
#include <QPixmap>
#include <QRandomGenerator>







Door::Door(int aX, int aY,  std::string aPixmapLink, QRect *aShape): Entities(aX, aY, aShape)
{
    std::list<QPixmap> *spriteDoor = new std::list<QPixmap>;
    spriteDoor->push_back(QPixmap(QString::fromStdString(aPixmapLink)));
    setItsPixMap(spriteDoor);
    RandomNumber();
}

void Door::OpenDoor(std::list<Player *> *somePlayer)
{
    if (itsAlreadyOpen == false)
    {
        for (Player *player : *somePlayer)
        {
            if (getItsShape()->intersects(*player->getItsShape()))
            {
                InDoor = true;
            }
        }
    }
}

void Door::RandomNumber()
{
    itsNumber = QRandomGenerator::global()->bounded(1, 4);
}

bool Door::getInDoor() const
{
    return InDoor;
}

void Door::setInDoor(bool newInDoor)
{
    InDoor = newInDoor;
}

int Door::getItsNumber() const
{
    return itsNumber;
}

void Door::setItsAlreadyOpen(bool newItsAlreadyOpen)
{
    itsAlreadyOpen = newItsAlreadyOpen;
}
