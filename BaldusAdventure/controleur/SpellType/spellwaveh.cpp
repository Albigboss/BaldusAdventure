#include "spellwaveh.h"
#include "qdebug.h"
#include "qpixmap.h"


spellWaveH::spellWaveH(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
    : Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteWaveH = new std::list<QPixmap>;
    SpriteWaveH->push_back(QPixmap(":/spell/images/sort/waveh-left.png"));
    SpriteWaveH->push_back(QPixmap(":/spell/images/sort/waveh-right.png"));
    setItsPixMap(SpriteWaveH);
    setIsProjectileSpell(true);

}


void spellWaveH::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy*>* someEnemy, std::list<Player *> *somePlayer)
{
    Q_UNUSED(somePlayer)
    bool xcolision = false;
    for (Obstacle* obstacle : *someObstacle)
    {
        if(getItsEntitie() != nullptr){
            if (getItsEntitie()->getItsShape()->intersects(*obstacle->getItsShape()))
            {
                xcolision = true;
                break;
            }
        }
    }
    for (Enemy* enemy : *someEnemy)
    {
        if(getItsEntitie() != nullptr){
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
        if(getItsDirection() == 1)
        {
            if(getItsEntitie() != nullptr){
                getItsEntitie()->getItsShape()->translate(5,0);
                getItsEntitie()->setItsX(getItsEntitie()->getItsX()+5);
            }

        }
        else
        {
            if(getItsEntitie() != nullptr){
            getItsEntitie()->getItsShape()->translate(-5,0);
            getItsEntitie()->setItsX(getItsEntitie()->getItsX()-5);
            }
        }
    }
    else
    {
        setItsEntitie(nullptr);
    }
}


