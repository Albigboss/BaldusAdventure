#ifndef SPELLMELEE_H
#define SPELLMELEE_H

#include "../spell.h"

/**
 * @brief The SpellMelee class
 */

class SpellMelee: public Spell
{

public:
    /**
     * @brief SpellMelee
     */
    SpellMelee(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);
};

#endif // SPELLMELEE_H
