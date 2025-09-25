#ifndef BAT_H
#define BAT_H

#include <list>
#include "../enemy.h"
#include "../obstacle.h"
#include "../player.h"


/**
 * @brief The Bat class
 * This class is used for the Bat enemy.
 * It manages the position of the Bat
 * Inherits the enemy class
 * @see Enemy
 * @author A12
 * @version 1
 */
class Bat: public Enemy
{

private:
    int itsXSpeed = 1; ///< speed X of the bat
    int itsYSpeed = 1; ///< speed y of the bat
    bool isNearPlayer = false; /// indicate if a bat is near a player
    std::list<Player*> *itsPlayers = nullptr; /// List of all the player

public:
    /**
     * @brief Bat
     * Construstor of the Bat Class
     * @param aLifePoints Number of life points of the Bat
     * @param aReward Number of gold the player earn when the Bat is killed
     * @param aDirection -1 if the direction goes to the left and 1 if the direction goes to the right.
     * @param aX position X of the Bat
     * @param aY position Y of the Bat
     * @param aShape invisble QRect of the Bat, its the hitbox of the Bat.
     */
    Bat(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player*> *somePlayers);

    //Destructeur Bat
    ~Bat();

    /**
     * @brief updateEnemyPosition
     * This function is used for the moving of the bat.
     * Their is the changed of direction at the and of a platform and the collision with wall.
     * @param someObstacles list of obstacle for the collision.
     * @see Obstacle
     */
    void updateEnemyPosition(std::list<Obstacle*> someObstacles);
};

#endif // BAT_H
