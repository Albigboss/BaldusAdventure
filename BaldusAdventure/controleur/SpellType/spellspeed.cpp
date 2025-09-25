#include "spellspeed.h"
#include "qpixmap.h"


SpellSpeed::SpellSpeed(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
        :Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteSpeed = new std::list<QPixmap>;
    SpriteSpeed->push_back(QPixmap(":/spell/images/sort/speed-left.png"));
    SpriteSpeed->push_back(QPixmap(":/spell/images/sort/speed-right.png"));
    setItsPixMap(SpriteSpeed);

}

void SpellSpeed::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer)
{
    Q_UNUSED(someObstacle)
    Q_UNUSED(someEnemy)
    Player *p = *somePlayer->begin();
    p->setItsXSpeedchange(1.5);

    getItsEntitie()->setItsX(p->getItsX());
    getItsEntitie()->setItsY(p->getItsY());

}
