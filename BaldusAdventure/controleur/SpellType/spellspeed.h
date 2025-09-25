#ifndef SPELLSPEED_H
#define SPELLSPEED_H

#include "../spell.h"
#include "../player.h"

/**
 * @brief The SpellSpeed class
 */
class SpellSpeed: public Spell
{

public:
    /**
     * @brief SpellSpeed
     */
    SpellSpeed(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);

};
#endif // SPELLSPEED_H
