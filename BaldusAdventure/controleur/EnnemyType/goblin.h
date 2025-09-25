#ifndef GOBLIN_H
#define GOBLIN_H
#include "../shooterenemy.h"
#include "../spell.h"
/**
 * @brief The Goblin class
 * Create the Goblin class, manage its movement
 * and check if it can shoot.
 * Inherits the ShooterEnemy class
 * @see ShooterEnemy
 * @author A12
 * @version 2
 */
class Goblin : public ShooterEnemy
{

private:
    int itsXSpeed = 1; ///< speed X of the goblin
    int itsYSpeed = 1; ///< speed X of the goblin
    bool itsShoot = false; ///< indicates if the gablin can shoot or not.

public:
    /**
     * @brief Goblin
     * Construstor of the Goblin Class
     * @param aLifePoints Number of life points of the Goblin
     * @param aReward Number of gold the player earn when the Goblin is killed
     * @param aDirection -1 if the direction goes to the left and 1 if the direction goes to the right.
     * @param aX position X of the Goblin
     * @param aY position Y of the Goblin
     * @param aShape invisble QRect of the Goblin, its the hitbox of the Goblin.
     */
    Goblin(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player*>* aPlayer);

    /**
     * @brief updateEnemyPosition
     * This function is used for the moving of the Goblin.
     * Their is the changed of direction at the and of a platform and the collision with wall.
     * @param someObstacles list of obstacle for the collision.
     * @see Obstacle
     */
    void updateEnemyPosition(std::list<Obstacle*> someObstacles);

    /**
     * @brief shoot
     * This function is look if can shoot
     * @param itsPlayer is the player
     */
    void shoot(Player * itsPlayer);
};

#endif // GOBLIN_H
