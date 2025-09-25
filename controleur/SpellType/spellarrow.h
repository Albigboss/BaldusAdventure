#ifndef SPELLARROW_H
#define SPELLARROW_H

#include "../spell.h"

/**
 * @brief The SpellArrow class
 */

class SpellArrow: public Spell
{

public:
    /**
     * @brief SpellArrow
     */
    SpellArrow(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);
};

#endif // SPELLARROW_H
