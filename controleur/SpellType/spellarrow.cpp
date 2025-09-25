#include "spellarrow.h"
#include "qpixmap.h"

SpellArrow::SpellArrow(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
    : Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteArrow = new std::list<QPixmap>;
    SpriteArrow->push_back(QPixmap(":/spell/images/sort/arrow-left.png"));
    SpriteArrow->push_back(QPixmap(":/spell/images/sort/arrow-right.png"));
    setItsPixMap(SpriteArrow);

    setIsProjectileSpell(true);
}


void SpellArrow::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy*>* someEnemy, std::list<Player *> *somePlayer)
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
                getItsEntitie()->getItsShape()->translate(7,0);
                getItsEntitie()->setItsX(getItsEntitie()->getItsX()+7);
            }

        }
        else
        {
            if(getItsEntitie() != nullptr){
                getItsEntitie()->getItsShape()->translate(-7,0);
                getItsEntitie()->setItsX(getItsEntitie()->getItsX()-7);
            }
        }
    }
    else
    {
        setItsEntitie(nullptr);
    }
}

