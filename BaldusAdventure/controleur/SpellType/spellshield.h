#ifndef SPELLSHIELD_H
#define SPELLSHIELD_H

#include "../spell.h"
#include "../player.h"

/**
 * @brief The SpellShield class
 */
class SpellShield: public Spell
{

public:
    /**
     * @brief SpellShield
     */
    SpellShield(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);

};

#endif // SPELLSHIELD_H
