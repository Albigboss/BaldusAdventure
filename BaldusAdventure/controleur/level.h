#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include <QPixmap>

#include "controleur/chest.h"
#include "controleur/enemy.h"
#include "controleur/EnnemyType/skeleton.h"
#include "shooterenemy.h"
#include "controleur/missiles.h"
#include "shop.h"
#include "player.h"
#include "obstacle.h"
#include "spell.h"

#include "door.h"
#include "key.h"
#include "shop.h"


using namespace std;


/**
 * @class Level
 * @brief Manages all game elements associated with a level.
 *
 * This class handles the creation, initialization, and management of game levels,
 * including players, enemies, shooter enemies, obstacles, background, and bonus items
 * like keys, chests, and doors. It supports initializing multiple level types (e.g., Level 1, 3, 4, Bonus),
 * resetting levels, and tracking player spell availability using timers.
 *
 * Inherits from QObject to allow use of signals and slots (e.g., for damage and spell cooldowns).
 *
 * @author A12
 * @version 2
 */
class Level : public QObject
{
    Q_OBJECT

private:
    QPixmap* itsBackground = nullptr; ///< Background image (map) of the level.

    int itsLevelNumber = 4;           ///< Current level number.
    int itsLevelWidth;                ///< Width of the level view.
    int itsLevelHeight;               ///< Height of the level view.

    std::list<Player*>* itsPlayers = nullptr;           ///< List of players in the level.
    std::list<Obstacle*>* itsObstacles = nullptr;       ///< List of obstacles in the level.
    std::list<Enemy*>* itsEnemy = nullptr;              ///< List of standard enemies.
    std::list<ShooterEnemy*>* itsShooterEnemy = nullptr;///< List of shooter-type enemies.

    Shop* itsShop = nullptr;         ///< Pointer to the shop object.
    Door* itsDoor = nullptr;         ///< Bonus door (entrance or teleport).
    Door* itsDoorExit = nullptr;     ///< Exit door.
    Key* itsKey = nullptr;           ///< Key required to unlock certain elements.
    Chest* itsChest = nullptr;       ///< Bonus chest containing rewards.

    Spell* spell1 = nullptr;         ///< First spell.
    Spell* spell2 = nullptr;         ///< Second spell.

    bool canThrowFirstSpell = true;  ///< Indicates if the player can cast the first spell.
    bool canThrowSecondSpell = true; ///< Indicates if the player can cast the second spell.

public:
    /**
     * @brief Constructs a new Level object.
     *
     * Initializes all necessary containers (players, enemies, obstacles, etc.) and configures
     * the basic properties of the level.
     *
     * @param nbLevel The level number to initialize.
     * @param parent Optional parent QObject.
     */
    Level(int nbLevel, QObject* parent = nullptr);

    /**
     * @brief Destructor for the Level class.
     */
    ~Level();

    /**
     * @brief Initializes level one.
     * Adds predefined enemies, obstacles, and items to the containers.
     */
    void initLevelOne();

    /**
     * @brief Initializes level three.
     * Adds enemies, shooter enemies, and other level-specific content.
     */
    void initLevelThree();

    /**
     * @brief Initializes level four.
     * Populates the level with relevant enemies and obstacles.
     */
    void initLevelFour();

    /**
     * @brief Initializes a random bonus level.
     * Chooses between 3 bonus level configurations using a random number and adds corresponding elements.
     */
    void initLevelBonus();

    /**
     * @brief Resets the level.
     * Clears all enemy, player, and obstacle lists. Useful when switching between levels.
     */
    void resetLevel();

    /**
     * @brief Removes an enemy from the level.
     * Called when an enemy is defeated.
     */
    void ennemyDead();

    //----------- Getters -----------

    std::list<Obstacle*>* getItsObstacles() const;
    std::list<Player*>* getItsPlayers() const;
    std::list<Enemy*>* getItsEnemy() const;
    std::list<ShooterEnemy*>* getItsShooterEnemy() const;

    QPixmap* getItsBackground() const;
    int getItsLevelWidth() const;
    int getItsLevelHeight() const;
    int getItsLevelNumber() const;

    bool getCanThrowFirstSpell() const;
    bool getCanThrowSecondSpell() const;

    Door* getItsDoor() const;
    Door* getItsDoorExit() const;
    Key* getItsKey() const;
    Chest* getItsChest() const;
    Shop* getItsShop() const;

public slots:
    /**
     * @brief Called when the player takes damage.
     * Can be connected to player signals for dynamic reactions.
     */
    void onPlayerDamage();

    /**
     * @brief Sets whether the player can throw the first spell.
     *
     * @param newCanThrowFirstSpell Set to true to enable casting the first spell.
     */
    void setCanThrowFirstSpell(bool newCanThrowFirstSpell = true);

    /**
     * @brief Sets whether the player can throw the second spell.
     *
     * @param newCanThrowSecondSpell Set to true to enable casting the second spell.
     */
    void setCanThrowSecondSpell(bool newCanThrowSecondSpell = true);
};


#endif // LEVEL_H
