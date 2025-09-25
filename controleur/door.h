#ifndef DOOR_H
#define DOOR_H
#include "controleur/player.h"
#include "entities.h"
#include <QObject>

/**
 * @class Door
 * @brief Manages doors and their open/closed state in the game.
 *
 * This class inherits from Entities and handles logic to check whether
 * a door is open, if a player is inside the door area, and assigns a random
 * number representing different bonus rooms.
 *
 * @see Entities
 * @author A12
 * @version 2
 */
class Door : public Entities
{
private:
    bool itsAlreadyOpen = false; ///< Tracks if the door has already been opened.
    int itsNumber = 1; ///< Identifies the bonus room number linked to this door.
    bool InDoor = false; ///< Indicates if a player is currently inside the door area.

public:
    /**
     * @brief Constructs a new Door object.
     *
     * Initializes the door position and hitbox, and assigns a random room number.
     *
     * @param aX X position of the door.
     * @param aY Y position of the door.
     * @param aShape Pointer to QRect representing the door's hitbox.
     */
    Door(int aX, int aY, std::string aPixmapLink, QRect* aShape);

    /**
     * @brief Checks if any player has entered the door area and updates door state.
     *
     * If the door is not already open, iterates through the list of players
     * and sets the InDoor flag to true if any player intersects with the door hitbox.
     *
     * @param somePlayer Pointer to a list of Player pointers.
     */
    void OpenDoor(std::list<Player*>* somePlayer);

    /**
     * @brief Generates a random number (1 to 3) to assign a random bonus room.
     */
    void RandomNumber();

    /**
     * @brief Gets whether a player is inside the door area.
     * @return true if player is inside, false otherwise.
     */
    bool getInDoor() const;

    /**
     * @brief Sets the flag indicating whether a player is inside the door.
     * @param newInDoor New value for InDoor.
     */
    void setInDoor(bool newInDoor);

    /**
     * @brief Sets the door's open state.
     * @param newItsAlreadyOpen New state indicating if door is already open.
     */
    void setItsAlreadyOpen(bool newItsAlreadyOpen);

    /**
     * @brief Gets the bonus room number associated with this door.
     * @return The room number (1 to 3).
     */
    int getItsNumber() const;
};

#endif // DOOR_H
