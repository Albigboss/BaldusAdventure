#ifndef MISSILES_H
#define MISSILES_H
#include "entities.h"
#include "obstacle.h"

/**
 * @class Missiles
 * @brief Represents a projectile fired by an enemy.
 *
 * This class creates and manages enemy projectiles (missiles) that move across the screen
 * and detect collisions with obstacles. Inherits from the Entities class.
 *
 * The missile moves in a specified direction with a fixed speed and stops upon collision
 * with obstacles such as walls or traps.
 *
 * @author A12
 * @version 2
 */
class Missiles : public Entities
{
private:
    int itsXSpeed = 2;        ///< Horizontal speed of the missile.
    int itsDirection = 1;     ///< Direction of movement: 1 for right, -1 for left.
    bool itsColision = false; ///< Flag indicating whether the missile has collided.

public:
    /**
     * @brief Constructs a new Missiles object.
     *
     * Initializes a missile with direction, position, hitbox, and collision status.
     *
     * @param aDirection Direction of movement (1 for right, -1 for left).
     * @param aX Initial X position of the missile.
     * @param aY Initial Y position of the missile.
     * @param aShape Invisible QRect hitbox of the missile.
     * @param aColision Initial collision state.
     */
    Missiles(int aDirection, int aX, int aY, QRect *aShape, bool aColision);

    /**
     * @brief Updates missile position and checks for collisions with obstacles.
     *
     * The missile is moved horizontally. If it intersects any obstacle, movement is stopped.
     *
     * @param someObstacles List of obstacles to check for collisions.
     * @see Obstacle
     */
    void updateMissiles(std::list<Obstacle*> someObstacles);

    //----------- Getters and Setters -----------

    /**
     * @brief Sets the direction of the missile.
     * @param newItsDirection New direction value (1 or -1).
     */
    void setItsDirection(int newItsDirection);

    /**
     * @brief Gets the current direction of the missile.
     * @return Direction of the missile.
     */
    int getItsDirection() const;
};


#endif // MISSILES_H
