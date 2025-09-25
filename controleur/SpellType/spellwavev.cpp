#include "SpellWaveV.h"
#include "qpixmap.h"





SpellWaveV::SpellWaveV(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
    : Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteWaveV = new std::list<QPixmap>;
    SpriteWaveV->push_back(QPixmap(":/spell/images/sort/wave-up.png"));
    SpriteWaveV->push_back(QPixmap(":/spell/images/sort/wave-up.png"));
    setItsPixMap(SpriteWaveV);
    setIsProjectileSpell(true);
}


void SpellWaveV::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy*>* someEnemy, std::list<Player *> *somePlayer)
{
    Q_UNUSED(somePlayer)
    bool xcolision = false;
    for (Obstacle* obstacle : *someObstacle)
    {
        if(getItsEntitie() != nullptr)
        {
            if (getItsEntitie()->getItsShape()->intersects(*obstacle->getItsShape()))
            {
                if(obstacle->getItsType() == WALL)
                {
                    xcolision = true;
                    break;
                }
            }
        }
    }
    for (Enemy* enemy : *someEnemy)
    {
        if(getItsEntitie() != nullptr)
        {
            if (getItsEntitie()->getItsShape()->intersects(*enemy->getItsShape()))
            {
                enemy->takeDamage(getItsDamage());
                xcolision = true;
                break;
            }
        }
    }

    // Si aucune collision horizontale, appliquer la translation horizontale
    if (!xcolision)
    {
        if(getItsEntitie() != nullptr){
            getItsEntitie()->getItsShape()->translate(0,-5);
            getItsEntitie()->setItsY(getItsEntitie()->getItsY()-5);
        }
    }
    else
        setItsEntitie(nullptr);

}


