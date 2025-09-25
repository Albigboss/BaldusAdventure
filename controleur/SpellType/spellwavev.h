#ifndef SPELLWAVEV_H
#define SPELLWAVEV_H

#include "../spell.h"


/**
 * @brief The SpellWaveV class
 */
class SpellWaveV: public Spell
{

public:
    /**
     * @brief SpellWaveV
     */
    SpellWaveV(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);
};

#endif // SPELLWAVEV_H
