#ifndef SPELLWAVEVLARGE_H
#define SPELLWAVEVLARGE_H

#include "controleur/spell.h"
/**
 * @brief The SpellWaveVLarge class
 */

class SpellWaveVLarge: public Spell
{

public:
    /**
     * @brief SpellWaveVLarge
     */
    SpellWaveVLarge(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType);

    /**
     * @brief updateSpell
     * @param someObstacle
     * @param someEnemy
     * @param somePlayer
     */
    void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer);
};


#endif // SPELLWAVEVLARGE_H
