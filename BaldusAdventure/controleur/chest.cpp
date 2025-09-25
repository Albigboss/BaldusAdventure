#include "chest.h"
#include "QtCore/qdebug.h"
#include <QPixmap>

Chest::Chest(int aX, int aY, std::string aPixmapLink, QRect *aShape) : Entities(aX, aY, aShape)
{
    std::list<QPixmap> *spriteDoor = new std::list<QPixmap>;
    spriteDoor->push_back(QPixmap(QString::fromStdString(aPixmapLink)));
    setItsPixMap(spriteDoor);
}

void Chest::ChestTake(Player *aPlayer)
{
    if (getItsShape()->intersects(*aPlayer->getItsShape()) && itsTakeChest == false)
    {
        itsTakeChest = true;
        if (aPlayer->getItsRemainingHearts() != 3)
        {
            aPlayer->setItsRemainingHearts(aPlayer->getItsRemainingHearts()+1);
        }
        else
        {
            aPlayer->setItsPiece(aPlayer->getItsPiece()+30);
        }
    }
}
