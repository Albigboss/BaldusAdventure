#include "bat.h"
#include "qdebug.h"
#include "qpixmap.h"
#include <math.h>

Bat::Bat(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player *> *somePlayers)
    :   Enemy(aLifePoints, aReward, aDirection, aX, aY, aShape), itsPlayers(somePlayers)
{
    std::list<QPixmap> *SpriteBat = new std::list<QPixmap>;
    SpriteBat->push_back(QPixmap(":/entites/images/entites/bat-left-1.png"));
    SpriteBat->push_back(QPixmap(":/entites/images/entites/bat-right-1.png"));
    this->setItsPixMap(SpriteBat);
}

Bat::~Bat()
{
    itsPlayers = nullptr;
}

void Bat::updateEnemyPosition(std::list<Obstacle *> someObstacles)
{
    QRect CurrentBat = *getItsShape();

    Player *p = *itsPlayers->begin();

    int distX = abs(p->getItsX() - this->getItsX());
    int distY = abs(p->getItsY() - this->getItsY());
    isNearPlayer = (sqrt(distX*distX + distY*distY) < 450);
    if (!isNearPlayer)
        return;

    int dx = (p->getItsX() > this->getItsX()) ? 1 : -1;
    setItsDirection(dx);
    int dy = (p->getItsY() > this->getItsY() + this->getItsShape()->height() / 2) ? 1 : -1;


    bool collisionXY = false;
    bool collisionX = false;
    bool collisionY = false;

    for (Obstacle* obstacle : someObstacles)
    {
        if (CurrentBat.translated(dx, dy).intersects(*obstacle->getItsShape()))
            collisionXY = true;
        if (CurrentBat.translated(dx, 0).intersects(*obstacle->getItsShape()))
            collisionX = true;
        if (CurrentBat.translated(0, dy).intersects(*obstacle->getItsShape()))
            collisionY = true;
    }

    if (!collisionXY)
    {
        getItsShape()->translate(dx, dy);
        setItsX(getItsX() + dx);
        setItsY(getItsY() + dy);
    }
    else {
        if (!collisionX)
        {
            getItsShape()->translate(dx, 0);
            setItsX(getItsX() + dx);
        }
        if (!collisionY)
        {
            getItsShape()->translate(0, dy);
            setItsY(getItsY() + dy);
        }
    }
}

