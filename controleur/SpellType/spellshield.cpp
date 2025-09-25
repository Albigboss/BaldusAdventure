#include "spellshield.h"
#include "qdebug.h"
#include "qpixmap.h"


SpellShield::SpellShield(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDirection, SpellType aType)
    :Spell(aDamage, aReloadTime, aPrice, aRange, aDirection, aMaxDirection, aType)
{
    std::list<QPixmap> *SpriteShield = new std::list<QPixmap>;
    SpriteShield->push_back(QPixmap(":/spell/images/sort/shield.png"));
    SpriteShield->push_back(QPixmap(":/spell/images/sort/shield.png"));
    setItsPixMap(SpriteShield);

}

void SpellShield::updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer)
{
    Q_UNUSED(someObstacle)
    Q_UNUSED(someEnemy)
    Player *p = *somePlayer->begin();
    getItsEntitie()->setItsX(p->getItsX());
    getItsEntitie()->setItsY(p->getItsY());
}
