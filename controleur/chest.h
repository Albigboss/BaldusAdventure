#ifndef CHEST_H
#define CHEST_H
#include "controleur/player.h"
#include "entities.h"
/**
 * @class Chest
 * @brief Manages the chest in the bonus room and checks if it can be opened.
 *
 * Inherits from Entities and handles the logic to determine if a player
 * can take the chest contents, ensuring it can only be taken once.
 *
 * @see Entities
 * @author A12
 * @version 2
 */
class Chest : public Entities
{
private:
    bool itsTakeChest = false; ///< Flag to ensure the chest can only be taken once.

public:
    /**
     * @brief Constructs a new Chest object.
     *
     * @param aX X position of the chest.
     * @param aY Y position of the chest.
     * @param aShape Pointer to QRect representing the chest's hitbox.
     */
    Chest(int aX, int aY, std::string aPixmapLink, QRect* aShape);

    /**
     * @brief Checks if the player can take the chest and applies effects.
     *
     * If the player intersects with the chest hitbox and the chest hasn't been taken yet,
     * it marks the chest as taken and either increases the player's hearts by one (up to 3)
     * or adds 30 pieces if hearts are full.
     *
     * @param aPlayer Pointer to the Player interacting with the chest.
     */
    void ChestTake(Player* aPlayer);
};


#endif // CHEST_H
