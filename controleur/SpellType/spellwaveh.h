#ifndef SPELLWAVEH_H
#define SPELLWAVEH_H

#include "../spell.h"

/**
 * @brief The spellWaveH class
 */

class spellWaveH: public Spell
{

public:
    /**
     * @brief spellWaveH
     */
    spellWaveH(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);
};

#endif // SPELLWAVEH_H
