#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "entities.h"

/**
 * @enum ObstacleType
 * @brief Enumerates the different types of obstacles.
 *
 * - WALL: A solid wall that blocks movement.
 * - TRAP: A harmful obstacle that causes damage.
 * - TRAVERSABLE: A platform that can be passed through from certain directions.
 */
enum ObstacleType
{
    WALL,         ///< A solid wall.
    TRAP,         ///< A harmful trap.
    TRAVERSABLE   ///< A passable platform.
};

/**
 * @class Obstacle
 * @brief Represents an obstacle in the game.
 *
 * The Obstacle class defines various environmental elements that interact with the player,
 * such as walls, traps, and traversable platforms. It inherits from the Entities class.
 *
 * Each obstacle has a specific type (WALL, TRAP, TRAVERSABLE) and a QRect hitbox used for collision detection.
 *
 * @author A12
 * @version 2
 */
class Obstacle : public Entities
{
private:
    ObstacleType itsType; ///< Type of the obstacle (WALL, TRAP, or TRAVERSABLE).

public:
    /**
     * @brief Constructs an Obstacle object.
     *
     * Initializes an obstacle with a specific position, type, shape, and optionally a pixmap for rendering.
     *
     * @param aX The X coordinate of the obstacle.
     * @param aY The Y coordinate of the obstacle.
     * @param aType The type of the obstacle (WALL, TRAP, or TRAVERSABLE).
     * @param aShape The hitbox of the obstacle (invisible QRect used for collision detection).
     * @param aPixmapLink (Optional) Path to the image to display for the obstacle. Default is ":/menu/images/defaultPixmap".
     */
    Obstacle(int aX, int aY, ObstacleType aType, QRect* aShape, std::string aPixmapLink = ":/menu/images/defaultPixmap");

    /**
     * @brief Returns the type of the obstacle.
     *
     * @return ObstacleType The obstacle's type (WALL, TRAP, or TRAVERSABLE).
     */
    ObstacleType getItsType() const;
};


#endif // OBSTACLE_H
