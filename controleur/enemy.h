#ifndef ENEMY_H
#define ENEMY_H
#include "controleur/obstacle.h"
#include "entities.h"
#include <list>

/**
 * @class Enemy
 * @brief Represents an enemy entity in the game.
 *
 * The Enemy class inherits from Entities and models the behavior and properties
 * of enemies in the game, including life points, movement direction, and rewards
 * given to the player upon defeat.
 *
 * This is an abstract base class as it contains a pure virtual function that must
 * be implemented by derived enemy types to define their movement behavior.
 *
 * @see Entities
 * @author A12
 * @version 2
 */
class Enemy : public Entities
{
private:
    int itsLifePoints; ///< Current health points of the enemy.
    int itsReward; ///< Amount of gold rewarded to the player when the enemy is defeated.
    int itsDirection; ///< Movement direction: -1 for left, 1 for right.

public:
    /**
     * @brief Constructs a new Enemy object.
     *
     * Initializes the enemy with life points, reward value, direction, position, and hitbox.
     *
     * @param aLifePoints Initial life points of the enemy.
     * @param aReward Gold rewarded to the player upon enemy's death.
     * @param aDirection Movement direction (-1 for left, 1 for right).
     * @param aX X position of the enemy.
     * @param aY Y position of the enemy.
     * @param aShape Pointer to QRect representing the enemy's hitbox.
     */
    Enemy(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect* aShape);

    /**
     * @brief Updates the enemy's position.
     *
     * Pure virtual function that must be overridden by subclasses to define
     * how the enemy moves, typically taking into account obstacles.
     *
     * @param someObstacles List of obstacles the enemy must navigate around.
     */
    virtual void updateEnemyPosition(std::list<Obstacle*> someObstacles) = 0;

    /**
     * @brief Applies damage to the enemy.
     *
     * Decreases the enemy's life points by the specified damage amount.
     *
     * @param damage Amount of damage inflicted.
     */
    void takeDamage(int damage);

    //----------- Getters and Setters -----------

    /**
     * @brief Gets the gold reward value.
     * @return The reward amount.
     */
    int getItsReward() const;

    /**
     * @brief Gets the current movement direction.
     * @return The direction (-1 for left, 1 for right).
     */
    int getItsDirection() const;

    /**
     * @brief Sets the movement direction.
     * @param newItsDirection New direction value (-1 or 1).
     */
    void setItsDirection(int newItsDirection);

    /**
     * @brief Gets the current life points.
     * @return The enemy's life points.
     */
    int getItsLifePoints() const;

    /**
     * @brief Sets the current life points.
     * @param newItsLifePoints New life points value.
     */
    void setItsLifePoints(int newItsLifePoints);
};


#endif // ENEMY_H
