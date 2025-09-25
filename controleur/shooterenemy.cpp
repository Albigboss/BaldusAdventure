#include "shooterenemy.h"






bool ShooterEnemy::getisEnnemyColided() const
{
    return isEnnemyColided;
}


ShooterEnemy::ShooterEnemy(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player *> *aPlayer):Enemy(aLifePoints, aReward, aDirection, aX, aY, aShape), somePlayer(aPlayer)
{
    itsMissiles = new Missiles(1, 100, 100, new QRect(100, 100, 12, 4), false);
}

std::list<Player *> *ShooterEnemy::getSomePlayer() const
{
    return somePlayer;
}

Missiles *ShooterEnemy::getItsMissiles() const
{
    return itsMissiles;
}
