#ifndef SPELL_H
#define SPELL_H
#include "controleur/enemy.h"
#include "controleur/obstacle.h"
#include "spelltype.h"

/**
 * @brief The Spell class
 */
class Player;

/**
 * @class Spell
 * @brief Abstract base class representing a spell in the game.
 *
 * The Spell class encapsulates the common attributes and behaviors of spells used by players or enemies.
 * It stores information such as damage, reload time, price, range, direction, and graphical representation.
 * It also provides an abstract method for updating the spell's state, to be implemented by derived spell types.
 *
 * @author A12
 * @version V2
 */
class Spell : public QObject
{
    Q_OBJECT

private:
    unsigned int itsDamage; ///< Damage dealt by the spell.
    unsigned int itsReloadTime; ///< Time needed to reload or cooldown before next use.
    int itsPrice; ///< Cost of the spell.
    int itsRange; ///< Range of the spell.
    int itsDirection = 1; ///< Direction of the spell [0 = not set, 1 = right, -1 = left].
    int itsMaxDistance = 0; ///< Maximum travel distance before the spell disappears.
    bool isProjectileSpell = false; ///< Indicates if the spell is a projectile.
    SpellType itsType; ///< Type/category of the spell.
    Entities *itsEntitie = nullptr; ///< Pointer to the entity that cast the spell.
    std::list<QPixmap> *itsPixMap = nullptr; ///< List of QPixmap frames representing the spell's animation.

public:
    /**
     * @brief Constructs a new Spell object.
     *
     * @param aDamage The damage dealt by the spell.
     * @param aReloadTime The reload or cooldown time before the spell can be used again.
     * @param aPrice The price or cost of the spell.
     * @param aRange The effective range of the spell.
     * @param aDirection The initial direction of the spell (0 = not set, 1 = right, -1 = left).
     * @param aMaxDistance The maximum distance the spell can travel before disappearing.
     * @param aType The type/category of the spell.
     */
    Spell(int aDamage, int aReloadTime, int aPrice, int aRange, int aDirection, int aMaxDistance, SpellType aType);

    /**
     * @brief Updates the spell's state.
     *
     * This is a pure virtual method that derived classes must implement to define
     * how the spell interacts with obstacles, enemies, and players.
     *
     * @param someObstacle List of obstacles in the game environment.
     * @param someEnemy List of enemy entities that the spell can affect.
     * @param somePlayer List of player entities that the spell can affect.
     */
    virtual void updateSpell(std::list<Obstacle *> *someObstacle, std::list<Enemy *> *someEnemy, std::list<Player *> *somePlayer) = 0;

    //-----------Getters and Setters-----------

    /**
     * @brief Gets the spell type.
     * @return SpellType The type of the spell.
     */
    SpellType getItsType() const;

    /**
     * @brief Gets the damage of the spell.
     * @return int Damage value.
     */
    int getItsDamage() const;

    /**
     * @brief Gets the reload time of the spell.
     * @return unsigned int Reload time in milliseconds or relevant unit.
     */
    unsigned int getItsReloadTime() const;

    /**
     * @brief Gets the price of the spell.
     * @return int Price value.
     */
    int getItsPrice() const;

    /**
     * @brief Gets the range of the spell.
     * @return int Range value.
     */
    int getItsRange() const;

    /**
     * @brief Gets the direction of the spell.
     * @return int Direction (0 = not set, 1 = right, -1 = left).
     */
    int getItsDirection() const;

    /**
     * @brief Sets the direction of the spell.
     * @param newItsDirection New direction value.
     */
    void setItsDirection(int newItsDirection);

    /**
     * @brief Gets the maximum distance the spell can travel.
     * @return int Maximum distance.
     */
    int getItsMaxDistance() const;

    /**
     * @brief Sets the maximum distance the spell can travel.
     * @param newItsMaxDistance New maximum distance.
     */
    void setItsMaxDistance(int newItsMaxDistance);

    /**
     * @brief Gets the entity that cast the spell.
     * @return Entities* Pointer to the casting entity.
     */
    Entities *getItsEntitie() const;

    /**
     * @brief Sets the entity that cast the spell.
     * @param newItsEntitie Pointer to the new casting entity.
     */
    void setItsEntitie(Entities *newItsEntitie);

    /**
     * @brief Sets whether the spell is a projectile.
     * @param newIsProjectileSpell True if the spell is a projectile, false otherwise.
     */
    void setIsProjectileSpell(bool newIsProjectileSpell);

    /**
     * @brief Checks if the spell is a projectile.
     * @return true If the spell is a projectile.
     * @return false Otherwise.
     */
    bool getIsProjectileSpell() const;

    /**
     * @brief Gets the list of QPixmap frames representing the spell.
     * @return std::list<QPixmap>* Pointer to the pixmap list.
     */
    std::list<QPixmap> *getItsPixMap() const;

    /**
     * @brief Sets the list of QPixmap frames representing the spell.
     * @param newItsPixMap Pointer to the new pixmap list.
     */
    void setItsPixMap(std::list<QPixmap> *newItsPixMap);
};


#endif // SPELL_H


