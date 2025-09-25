#include "skeleton.h"
#include "qdebug.h"
#include "qpixmap.h"

Skeleton::Skeleton(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape)
    :   Enemy(aLifePoints, aReward, aDirection, aX, aY, aShape)
{
    std::list<QPixmap> *SpriteSkeleton = new std::list<QPixmap>;
    SpriteSkeleton->push_back(QPixmap(":/entites/images/entites/skeleton-left-1.png"));
    SpriteSkeleton->push_back(QPixmap(":/entites/images/entites/skeleton-right-1.png"));
    this->setItsPixMap(SpriteSkeleton);
}

void Skeleton::updateEnemyPosition(std::list<Obstacle *> someObstacles)
{

    QRect CurrentSkeleton = *getItsShape();
    QRect fictiveSkeletonX = CurrentSkeleton.translated(itsXSpeed * getItsDirection(), 0);
    QRect fictiveSkeletonY = CurrentSkeleton.translated(0, itsYSpeed);


    bool yCollision = false;
    bool xCollision = false;

    for (Obstacle* obstacle : someObstacles)
    {
        // Check if their is a collision between the player and X axes
        if (fictiveSkeletonX.intersects(*obstacle->getItsShape()))
        {
            xCollision = true;
            setItsDirection(-getItsDirection());

        }

        // Check if their is a collision between the player and Y axes
        if (fictiveSkeletonY.intersects(*obstacle->getItsShape()))
        {
            yCollision = true;

            if(obstacle->getItsShape()->left() > fictiveSkeletonX.left())
            {
                setItsDirection(-getItsDirection());
            }
            else if(obstacle->getItsShape()->right() < fictiveSkeletonX.right())
            {
                setItsDirection(-getItsDirection());
            }
        }
    }

    // Move if their is no collision.
    if (!xCollision)
    {
        getItsShape()->translate(itsXSpeed * getItsDirection(), 0);
        setItsX(getItsX() + itsXSpeed * getItsDirection());
    }
    if (!yCollision)
    {
        getItsShape()->translate(0, itsYSpeed);
        setItsY(getItsY() + itsYSpeed);
    }
}




