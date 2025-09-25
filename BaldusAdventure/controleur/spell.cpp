#include "spell.h"



Spell::Spell(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDistance, SpellType aType)
    : itsDamage(aDamage), itsReloadTime(aReloadTime), itsPrice(aPrice), itsRange(aRange), itsDirection(aDirection), itsMaxDistance(aMaxDistance), itsType(aType)
{}

bool Spell::getIsProjectileSpell() const
{
    return isProjectileSpell;
}

int Spell::getItsPrice() const
{
    return itsPrice;
}


SpellType Spell::getItsType() const
{
    return itsType;
}


int Spell::getItsDamage() const
{
    return itsDamage;
}
int Spell::getItsRange() const
{
    return itsRange;
}

unsigned int Spell::getItsReloadTime() const
{
    return itsReloadTime;
}

int Spell::getItsDirection() const
{
    return itsDirection;
}

void Spell::setItsDirection(int newItsDirection)
{
    itsDirection = newItsDirection;
}


int Spell::getItsMaxDistance() const
{
    return itsMaxDistance;
}

void Spell::setItsMaxDistance(int newItsMaxDistance)
{
    itsMaxDistance = newItsMaxDistance;
}

Entities *Spell::getItsEntitie() const
{
    return itsEntitie;
}

void Spell::setItsEntitie(Entities *newItsEntitie)
{
    itsEntitie = newItsEntitie;
}

void Spell::setIsProjectileSpell(bool newIsProjectileSpell)
{
    isProjectileSpell = newIsProjectileSpell;
}

std::list<QPixmap> *Spell::getItsPixMap() const
{
    return itsPixMap;
}

void Spell::setItsPixMap(std::list<QPixmap> *newItsPixMap)
{
    itsPixMap = newItsPixMap;
}

