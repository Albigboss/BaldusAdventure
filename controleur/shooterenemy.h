#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H
#include "controleur/missiles.h"
#include "enemy.h"
#include "player.h"



/**
 * @class ShooterEnemy
 * @brief Abstract class representing an enemy that can shoot projectiles.
 *
 * The ShooterEnemy class extends the Enemy base class and adds functionality for shooting missiles
 * and detecting collisions with players. It is an abstract class and must be subclassed to define
 * specific enemy behavior (e.g., movement and shooting logic).
 *
 * @see Enemy
 * @author A12
 * @version 2
 */
class ShooterEnemy : public Enemy
{
private:
    Missiles *itsMissiles = nullptr;              ///< Missile used by the enemy to shoot players.
    std::list<Player*>* somePlayer = nullptr;     ///< Reference to players in the game for hit detection.

public:
    bool isEnnemyColided = false; ///< True if a collision has occurred between the enemy and a player.

    /**
     * @brief Constructs a ShooterEnemy.
     * @param aLifePoints Number of life points.
     * @param aReward Gold rewarded to the player upon this enemy's death.
     * @param aDirection Direction the enemy is moving in (-1 = left, 1 = right).
     * @param aX X position in the game world.
     * @param aY Y position in the game world.
     * @param aShape QRect representing the hitbox of the enemy.
     * @param aPlayer Reference to the list of players in the game.
     */
    ShooterEnemy(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player*>* aPlayer);

    /**
     * @brief Virtual method to update the enemy's position.
     * Must be overridden by derived classes.
     * @param someObstacles A list of obstacles that affect movement.
     */
    virtual void updateEnemyPosition(std::list<Obstacle*> someObstacles) = 0;

    /**
     * @brief Virtual method to execute a shooting action.
     * Must be overridden by derived classes.
     * @param istPlayer The player targeted by the enemy's missile.
     */
    virtual void shoot(Player* istPlayer) = 0;

    /**
     * @brief Checks if the enemy has collided with a player.
     * @return True if a collision has occurred, false otherwise.
     */
    bool getisEnnemyColided() const;

    //----------- Getters -----------

    /**
     * @brief Returns the list of players.
     * @return Pointer to the list of players used for missile targeting.
     */
    std::list<Player *> *getSomePlayer() const;

    /**
     * @brief Returns the missile used by this enemy.
     * @return Pointer to the Missiles object.
     */
    Missiles *getItsMissiles() const;
};


#endif // SHOOTERENEMY_H
