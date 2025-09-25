#ifndef SPELLJUMP_H
#define SPELLJUMP_H

#include "../spell.h"
#include "../player.h"

/**
 * @brief The SpellJump class
 */

class SpellJump: public Spell
{

public:
    /**
     * @brief SpellJump
     */
    SpellJump(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);

};
#endif // SPELLJUMP_H
