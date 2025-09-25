#include "spellmelee.h"
#include "qpixmap.h"

SpellMelee::SpellMelee(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
    : Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteMelee = new std::list<QPixmap>;
    SpriteMelee->push_back(QPixmap(":/spell/images/sort/melee-left.png"));
    SpriteMelee->push_back(QPixmap(":/spell/images/sort/melee-right.png"));
    setItsPixMap(SpriteMelee);
    setIsProjectileSpell(true);
}


void SpellMelee::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy*>* someEnemy, std::list<Player *> *somePlayer)
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
                getItsEntitie()->getItsShape()->translate(4,0);
                getItsEntitie()->setItsX(getItsEntitie()->getItsX()+4);
            }
        }
        else
        {
            if(getItsEntitie() != nullptr){
                getItsEntitie()->getItsShape()->translate(-4,0);
                getItsEntitie()->setItsX(getItsEntitie()->getItsX()-4);
            }
        }
    }
    else
    {
        setItsEntitie(nullptr);
    }
}

