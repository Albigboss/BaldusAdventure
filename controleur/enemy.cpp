#include "enemy.h"
#include "QtCore/qdebug.h"




Enemy::Enemy(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape)
    : Entities(aX, aY, aShape), itsLifePoints(aLifePoints), itsReward(aReward), itsDirection(aDirection)
{

}


int Enemy::getItsReward() const
{
    return itsReward;
}

int Enemy::getItsDirection() const
{
    return itsDirection;
}

void Enemy::setItsDirection(int newItsDirection)
{
    itsDirection = newItsDirection;
}

int Enemy::getItsLifePoints() const
{
    return itsLifePoints;
}

void Enemy::setItsLifePoints(int newItsLifePoints)
{
    itsLifePoints = newItsLifePoints;
}

void Enemy::takeDamage(int damage)
{
    setItsLifePoints(getItsLifePoints()-damage);
}

