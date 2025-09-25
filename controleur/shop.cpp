#include "shop.h"
#include "controleur/SpellType/SpellWaveV.h"
#include "controleur/SpellType/spellarrow.h"
#include "controleur/SpellType/spelljump.h"
#include "controleur/SpellType/spellmelee.h"
#include "controleur/SpellType/spellshield.h"
#include "controleur/SpellType/spellspeed.h"
#include "controleur/SpellType/spellwaveh.h"
#include "controleur/SpellType/spellwavevlarge.h"
#include "qpixmap.h"

std::vector<Spell *> Shop::getItsSpells() const
{
    return itsSpells;
}

Spell *Shop::getSpell(int index)
{
    return itsSpells[index];
}

bool Shop::canOpenShop(std::list<Player *> listPlayer)
{
    for(Player *p : listPlayer)
    {
        if(getItsShape()->intersects(*p->getItsShape()))
        {
            return true;
        }
    }
    return false;
}

void Shop::selectSpellOne(int actualPage, int position)
{
    switch(actualPage){
    case 1:
        if(itsBoughtSpells[position] == nullptr)
        {
            itsBoughtSpells[position] = itsSpells[position];
        }
        itsFirstSelectedSpell = itsSpells[position];
        break;
    case 2:
        if(itsBoughtSpells[position+4] == nullptr)
        {
            itsBoughtSpells[position+4] = itsSpells[position+4];
        }
        itsFirstSelectedSpell = itsSpells[position+4];
        break;

    case 3:
        if(itsBoughtSpells[position+8] == nullptr)
        {
            itsBoughtSpells[position+8] = itsSpells[position+8];
        }
        itsFirstSelectedSpell = itsSpells[position+8];
        break;
    default:
        break;
    }
}

void Shop::selectSpellTwo(int actualPage, int position)
{
    switch(actualPage){
    case 1:
        if(itsBoughtSpells[position] == nullptr)
        {
            itsBoughtSpells[position] = itsSpells[position];
        }
        itsSecondSelectedSpell = itsSpells[position];
        break;
    case 2:
        if(itsBoughtSpells[position+4] == nullptr)
        {
            itsBoughtSpells[position+4] = itsSpells[position+4];
        }
        itsSecondSelectedSpell = itsSpells[position+4];
        break;

    case 3:
        if(itsBoughtSpells[position+8] == nullptr)
        {
            itsBoughtSpells[position+8] = itsSpells[position+8];
        }
        itsSecondSelectedSpell = itsSpells[position+8];
        break;
    default:
        break;
    }
}

Spell *Shop::getItsFirstSelectedSpell() const
{
    return itsFirstSelectedSpell;
}

Spell *Shop::getItsSecondSelectedSpell() const
{
    return itsSecondSelectedSpell;
}

Shop::Shop(int aX, int aY, std::string aPixmapLink) : Entities(aX, aY, new QRect(aX, aY, 100, 100))
{

    std::list<QPixmap> *spriteShop = new std::list<QPixmap>;
    spriteShop->push_back(QPixmap(QString::fromStdString(aPixmapLink)));
    setItsPixMap(spriteShop);

    Spell *spell1 = new SpellWaveV(1, 1000, 12, 10, 1, 0, WEAK);
    Spell *spell2 = new spellWaveH(1, 1000, 12, 200, 1, 0, WEAK);
    Spell *spell3 = new SpellMelee(2, 500, 12, 50, 1, 0, WEAK);
    Spell *spell4 = new SpellSpeed(0, 10000, 12, 0, 1, 0, WEAK);

    Spell *spell5 = nullptr;
    Spell *spell6 = new SpellWaveVLarge(2, 2000, 18, 100, 1, 0, AVERAGE);
    Spell *spell7 = new SpellJump(0, 10000, 18, 0, 1, 0, AVERAGE);
    Spell *spell8 = nullptr;

    Spell *spell9 = nullptr;
    Spell *spell10 = new SpellArrow(4, 3000, 25, 500, 1, 0, STRONG);
    Spell *spell11 = new SpellShield(0, 10000, 25, 0, 1, 0, STRONG);
    Spell *spell12 = nullptr;

    itsSpells.push_back(spell1);
    itsSpells.push_back(spell2);
    itsSpells.push_back(spell3);
    itsSpells.push_back(spell4);
    itsSpells.push_back(spell5);
    itsSpells.push_back(spell6);
    itsSpells.push_back(spell7);
    itsSpells.push_back(spell8);
    itsSpells.push_back(spell9);
    itsSpells.push_back(spell10);
    itsSpells.push_back(spell11);
    itsSpells.push_back(spell12);
    for(int i=0; i<itsSpells.size(); i++)
    {
        itsBoughtSpells.push_back(nullptr);
    }
}
