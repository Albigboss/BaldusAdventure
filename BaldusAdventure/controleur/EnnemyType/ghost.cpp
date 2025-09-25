#include "ghost.h"
#include "qdebug.h"
#include "qpixmap.h"
#include <math.h>

Ghost::Ghost(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player *> *somePlayers)
    :   Enemy(aLifePoints, aReward, aDirection, aX, aY, aShape), itsPlayers(somePlayers)
{
    std::list<QPixmap> *SpriteGhost = new std::list<QPixmap>;
    SpriteGhost->push_back(QPixmap(":/entites/images/entites/ghost-left-1.png"));
    SpriteGhost->push_back(QPixmap(":/entites/images/entites/ghost-right-1.png"));
    this->setItsPixMap(SpriteGhost);
}

Ghost::~Ghost()
{
    itsPlayers = nullptr;
}

void Ghost::updateEnemyPosition(std::list<Obstacle *> someObstacles)
{
    Q_UNUSED(someObstacles)

    Player *p = *itsPlayers->begin();

    int distX = abs(p->getItsX() - this->getItsX());
    int distY = abs(p->getItsY() - this->getItsY());
    isNearPlayer = (sqrt(distX*distX + distY*distY) < 500);
    if (!isNearPlayer)
        return;

    int dx = 0;
    int dy = 0;

    dx = (p->getItsX() > this->getItsX()) ? 1 : -1;
    dy = (p->getItsY() > this->getItsY() + this->getItsShape()->height() / 2) ? 1 : -1;

    setItsDirection(dx);



    if(p->getItsX()+10 > this->getItsX() &&  p->getItsX()-10 < this->getItsX()){
        dx = 0;
    }
    if(p->getItsY()+10 > this->getItsY()  &&  p->getItsY()-10 < this->getItsY()){
        dy = 0;
    }

    getItsShape()->translate(dx, dy);
    setItsX(getItsX() + dx);
    setItsY(getItsY() + dy);



}


