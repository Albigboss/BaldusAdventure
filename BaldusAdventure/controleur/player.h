#ifndef PLAYER_H
#define PLAYER_H
#include <QRect>
#include <QTimer>
#include "spell.h"
#include <list>
#include <QObject>
#include "entities.h"
#include "obstacle.h"
#include "enemy.h"

/**
 * @class Player
 * @brief The Player class handles the player character's logic, including movement, collision detection, and interactions with obstacles, enemies, and spells.
 *
 * The class inherits from Entities and manages player input (left/right movement, jump),
 * hitbox updates, health tracking, and spell usage with cooldowns.
 *
 * @author A12
 * @version 2
 */
class Player : public Entities
{
    Q_OBJECT

private:
    int itsRemainingHearts = 3;        ///< The number of remaining lives.
    int itsPiece = 0;                  ///< The number of coins or pieces collected by the player.

    bool itsRight = false;            ///< True if the right movement key is pressed.
    bool itsLeft = false;             ///< True if the left movement key is pressed.
    bool itsJump = false;             ///< True if the player is allowed to jump.

    bool isFirstSpell = false;        ///< True if the first spell should be launched.
    bool isSecondSpell = false;       ///< True if the second spell should be launched.
    Spell *itsFirstSpell = nullptr;   ///< Pointer to the first spell instance.
    Spell *itsSecondSpell = nullptr;  ///< Pointer to the second spell instance.

    int itsXSpeed = 0;                ///< Horizontal movement speed.
    float itsYSpeed = 0;              ///< Vertical movement speed (affected by gravity).
    int maxgrave = 2;                 ///< Gravity limit (maximum falling speed).
    bool itsWallJump = false;         ///< True if the player is currently wall jumping.
    bool canWallJump = false;         ///< True if the player is allowed to wall jump.

    double itsXSpeedchange = 1;       ///< Modifier to alter horizontal speed (e.g., for power-ups).
    double itsYSpeedchange = 1;       ///< Modifier to alter vertical speed (e.g., for jumps).
    int itsDirection = 1;             ///< Direction the player is facing (1 = right, -1 = left).

public:
    QTimer *itsFirstSpellcoolDown = nullptr;  ///< Timer managing cooldown for the first spell.
    QTimer *itsSecondSpellcoolDown = nullptr; ///< Timer managing cooldown for the second spell.

    /**
     * @brief Constructs a Player object.
     * @param aX Initial X position.
     * @param aY Initial Y position.
     * @param aShape Pointer to the player's rectangular hitbox.
     */
    Player(int aX, int aY, QRect *aShape);

    /**
     * @brief Destroys the Player object and deallocates spell and cooldown resources.
     */
    ~Player();

    /**
     * @brief Updates the player's position based on input and checks for collisions.
     * @param someObstacles List of all obstacles on the level.
     * @param someEnemy Pointer to list of all enemies.
     */
    void updatePlayer(std::list<Obstacle *> someObstacles, std::list<Enemy*>* someEnemy);

    /**
     * @brief Makes the player jump if allowed or perform a wall jump.
     */
    void jump();

    /**
     * @brief Reduces the player's life by one heart.
     */
    void loseHeart();

    // ------------------ Getters and Setters ------------------

    int getItsXSpeed() const;                       ///< Gets the horizontal speed.
    int getItsDirection() const;                    ///< Gets the direction the player is facing.
    void setItsDirection(int newItsDirection);      ///< Sets the direction the player is facing.

    void setItsRight(bool newItsRight);             ///< Sets the right movement flag.
    bool getItsRight() const;                       ///< Gets the right movement flag.

    void setItsLeft(bool newItsLeft);               ///< Sets the left movement flag.
    bool getItsLeft() const;                        ///< Gets the left movement flag.

    QRect getRect() const;                          ///< Returns the player hitbox rectangle.

    Spell *getItsFirstSpell() const;                ///< Gets the first spell instance.
    void setItsFirstSpell(Spell *newItsFirstSpell); ///< Sets the first spell instance.

    Spell *getItsSecondSpell() const;               ///< Gets the second spell instance.
    void setItsSecondSpell(Spell *newItsSecondSpell); ///< Sets the second spell instance.

    bool getIsFirstSpell() const;                   ///< Returns true if the first spell should be launched.
    void setIsFirstSpell(bool newIsFirstSpell);     ///< Sets the first spell activation flag.

    bool getIsSecondSpell() const;                  ///< Returns true if the second spell should be launched.
    void setIsSecondSpell(bool newIsSecondSpell);   ///< Sets the second spell activation flag.

    int getItsRemainingHearts() const;              ///< Gets the number of remaining hearts.
    void setItsRemainingHearts(int newItsRemainingHearts); ///< Sets the number of remaining hearts.

    int getItsPiece() const;                        ///< Gets the number of collected pieces.
    void setItsPiece(int newItsPiece);              ///< Sets the number of collected pieces.

    QTimer *getItsFirstSpellcoolDown() const;       ///< Gets the cooldown timer for the first spell.
    QTimer *getItsSecondSpellcoolDown() const;      ///< Gets the cooldown timer for the second spell.

    void setItsXSpeedchange(double newItsXSpeedchange); ///< Sets the horizontal speed multiplier.
    void setItsYSpeedchange(double newItsYSpeedchange); ///< Sets the vertical speed multiplier.

private slots:
    /**
     * @brief Triggered when the cooldown for the first spell ends.
     * Emits the SIG_FirstSpellTimerOff signal.
     * @see SIG_FirstSpellTimerOff
     */
    void onFirstSpellTimerOff();

    /**
     * @brief Triggered when the cooldown for the second spell ends.
     * Emits the SIG_SecondSpellTimerOff signal.
     * @see SIG_SecondSpellTimerOff
     */
    void onSecondSpellTimerOff();

signals:
    /**
     * @brief Signal emitted when the player is hit (e.g., by enemy or trap).
     */
    void SIG_playerDamage();

    /**
     * @brief Signal emitted when the first spell is ready to be used again.
     */
    void SIG_FirstSpellTimerOff();

    /**
     * @brief Signal emitted when the second spell is ready to be used again.
     */
    void SIG_SecondSpellTimerOff();

    /**
     * @brief Signal emitted to request a sound to be played.
     * @param soundID ID of the sound to play.
     */
    void SIG_SoundsToBePlayed(int soundID);
};


#endif // PLAYER_H
