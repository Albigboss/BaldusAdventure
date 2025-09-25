#include "key.h"
#include "QtCore/qdebug.h"

#include <QPixmap>


Key::Key(int aX, int aY, std::string aPixmapLink,QRect *aShape) : Entities(aX, aY, aShape)
{
    std::list<QPixmap> *spriteDoor = new std::list<QPixmap>;
    spriteDoor->push_back(QPixmap(QString::fromStdString(aPixmapLink)));
    setItsPixMap(spriteDoor);
}

void Key::KeyTake(Player* aPlayer)
{
    if (getItsShape()->intersects(*aPlayer->getItsShape()) && itsTakeKey == false)
    {
        itsTakeKey = true;
    }

}

bool Key::getItsTakeKey() const
{
    return itsTakeKey;
}
