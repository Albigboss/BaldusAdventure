#include "spelljump.h"
#include "qpixmap.h"

SpellJump::SpellJump(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
    :Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteJump = new std::list<QPixmap>;
    SpriteJump->push_back(QPixmap(":/spell/images/sort/jump-left.png"));
    SpriteJump->push_back(QPixmap(":/spell/images/sort/jump-right.png"));
    setItsPixMap(SpriteJump);
}

void SpellJump::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer)
{
    Q_UNUSED(someObstacle)
    Q_UNUSED(someEnemy)
    Player *p = *somePlayer->begin();
    p->setItsYSpeedchange(1.3);

    getItsEntitie()->setItsX(p->getItsX());
    getItsEntitie()->setItsY(p->getItsY());

}

