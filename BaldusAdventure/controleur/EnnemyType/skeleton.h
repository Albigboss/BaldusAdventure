#ifndef SKELETON_H
#define SKELETON_H

#include <list>
#include "../enemy.h"
#include "controleur/obstacle.h"

/**
 * @brief The Skeleton class
 * This class is used for the skeleton enemy.
 * It manages the position of the skeleton
 * Inherits the enemy class
 * @see Enemy
 * @author A12
 * @version 1
 */
class Skeleton: public Enemy
{

private:
    int itsXSpeed = 1; ///< speed X of the skeleton
    int itsYSpeed = 1; ///< speed y of the skeleton

public:
    /**
     * @brief Skeleton
     * Construstor of the skeleton Class
     * @param aLifePoints Number of life points of the skeleton
     * @param aReward Number of gold the player earn when the skeleton is killed
     * @param aDirection -1 if the direction goes to the left and 1 if the direction goes to the right.
     * @param aX position X of the skeleton
     * @param aY position Y of the skeleton
     * @param aShape invisble QRect of the skeleton, its the hitbox of the skeleton.
     */
    Skeleton(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape);

    /**
     * @brief updateEnemyPosition
     * This function is used for the moving of the skeleton.
     * Their is the changed of direction at the and of a platform and the collision with wall.
     * @param someObstacles list of obstacle for the collision.
     * @see Obstacle
     */
    void updateEnemyPosition(std::list<Obstacle*> someObstacles);
};

#endif // SKELETON_H
