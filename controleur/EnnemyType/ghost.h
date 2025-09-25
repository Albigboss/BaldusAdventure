#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "../enemy.h"
#include "../obstacle.h"
#include "../player.h"


/**
 * @brief The Ghost class
 * This class is used for the Ghost enemy.
 * It manages the position of the Ghost
 * Inherits the enemy class
 * @see Enemy
 * @author A12
 * @version 1
 */
class Ghost: public Enemy
{

private:
    int itsXSpeed = 1; ///< speed X of the Ghost
    int itsYSpeed = 1; ///< speed y of the Ghost
    bool isNearPlayer = false; /// indicate if a Ghost is near a player
    std::list<Player*> *itsPlayers = nullptr; /// List of all the player

public:
    /**
     * @brief Ghost
     * Construstor of the Ghost Class
     * @param aLifePoints Number of life points of the Ghost
     * @param aReward Number of gold the player earn when the Ghost is killed
     * @param aDirection -1 if the direction goes to the left and 1 if the direction goes to the right.
     * @param aX position X of the Ghost
     * @param aY position Y of the Ghost
     * @param aShape invisble QRect of the Ghost, its the hitbox of the Ghost.
     */
    Ghost(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player*> *somePlayers);

    //Destructeur Ghost
    ~Ghost();

    /**
     * @brief updateEnemyPosition
     * This function is used for the moving of the Ghost.
     * Their is the changed of direction at the and of a platform and the collision with wall.
     * @param someObstacles list of obstacle for the collision.
     * @see Obstacle
     */
    void updateEnemyPosition(std::list<Obstacle*> someObstacles);
};


#endif // GHOST_H
