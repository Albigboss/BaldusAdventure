#include "missiles.h"

#include <QPixmap>



#include <QDebug>




Missiles::Missiles(int aDirection, int aX, int aY, QRect *aShape, bool aColision) : Entities(aX, aY, aShape), itsDirection(aDirection), itsColision(aColision)
{

}

void Missiles::updateMissiles(std::list<Obstacle *> someObstacles)
{
    QRect CurrentMissiles = *getItsShape();
    QRect fictiveMissilesX = CurrentMissiles.translated(itsXSpeed * itsDirection, 0);

    bool xCollision = false;

    for (Obstacle* obstacle : someObstacles)
    {
        // Check if their is a collision between the player and X axes
        if (fictiveMissilesX.intersects(*obstacle->getItsShape()))
        {

            xCollision = true;
        }
    }

    // Move if their is no collision.
    if (!xCollision)
    {
        getItsShape()->translate(itsXSpeed * itsDirection, 0);
        setItsX(getItsX() + itsXSpeed * itsDirection);
    }
}

void Missiles::setItsDirection(int newItsDirection)
{
    itsDirection = newItsDirection;
}

int Missiles::getItsDirection() const
{
    return itsDirection;
}
