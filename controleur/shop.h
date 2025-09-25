#ifndef SHOP_H
#define SHOP_H
#include "controleur/player.h"
#include "spell.h"
#include "entities.h"

#include <vector>

/**
 * @class Shop
 * @brief Represents a shop entity in the game where players can buy and select spells.
 * @author A12
 * @version V2
 *
 * The Shop class manages a collection of available spells and allows players to buy and equip them.
 * It provides functionality to check player proximity, handle spell selection across pages,
 * and store purchased spells.
 *
 * Inherits from Entities.
 */
class Shop : public Entities
{
    Q_OBJECT

private:
    Spell *itsFirstSelectedSpell = nullptr;      ///< First spell selected by the player.
    Spell *itsSecondSelectedSpell = nullptr;     ///< Second spell selected by the player.
    std::vector<Spell*> itsSpells;               ///< All spells available in the shop.
    std::vector<Spell*> itsBoughtSpells;         ///< Spells bought by the player.

public:
    /**
     * @brief Constructs a Shop entity.
     * @param aX The X coordinate of the shop in the game world.
     * @param aY The Y coordinate of the shop in the game world.
     * @param aPixmapLink Optional path to the shop sprite (defaults to a generic image).
     */
    Shop(int aX, int aY, std::string aPixmapLink = ":/menu/images/defaultPixmap");

    /**
     * @brief Returns the list of all spells available in the shop.
     * @return A vector of pointers to Spell objects.
     */
    std::vector<Spell *> getItsSpells() const;

    /**
     * @brief Retrieves a specific spell by index.
     * @param index Index of the spell in the spell list.
     * @return Pointer to the selected Spell.
     */
    Spell *getSpell(int index);

    /**
     * @brief Checks if any player is close enough to open the shop.
     * @param listPlayer A list of all players to check for proximity.
     * @return True if any player intersects with the shop's area, false otherwise.
     */
    bool canOpenShop(std::list<Player*> listPlayer);

    /**
     * @brief Selects the first spell to equip based on the shop page and spell position.
     * If not already bought, the spell is marked as bought.
     * @param actualPage Current shop page (1 to 3).
     * @param position Index of the spell in the page (0 to 3).
     */
    void selectSpellOne(int actualPage, int position);

    /**
     * @brief Selects the second spell to equip based on the shop page and spell position.
     * If not already bought, the spell is marked as bought.
     * @param actualPage Current shop page (1 to 3).
     * @param position Index of the spell in the page (0 to 3).
     */
    void selectSpellTwo(int actualPage, int position);

    /**
     * @brief Returns the first spell currently selected by the player.
     * @return Pointer to the selected Spell.
     */
    Spell *getItsFirstSelectedSpell() const;

    /**
     * @brief Returns the second spell currently selected by the player.
     * @return Pointer to the selected Spell.
     */
    Spell *getItsSecondSelectedSpell() const;
};


#endif // SHOP_H
