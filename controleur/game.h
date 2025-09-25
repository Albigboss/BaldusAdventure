#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include <QObject>
#include "level.h"
#include "shooterenemy.h"

using namespace std;


/**
 * @class Game
 * @brief Manages the overall game logic, calling model updates regularly.
 *
 * This class encapsulates the core loop of the game by updating all entities (players, enemies, etc.)
 * at fixed intervals using a QTimer. It also handles score computation and leaderboard file writing.
 *
 * @see Level
 * @author A12
 * @version 2
 */
class Game : public QObject
{
    Q_OBJECT

private:
    Level* itsLevel = nullptr;       ///< Pointer to the current level.
    unsigned int itsElapsedTime = 0; ///< Elapsed time since game start in milliseconds.
    unsigned int itsScore = 0;       ///< Player score, computed during gameplay.

public:
    QTimer* itsQTimer = nullptr;     ///< Game timer that triggers updates every 8ms.

    /**
     * @brief Constructs a new Game object.
     * Initializes a new level and starts the update timer.
     */
    Game();

    /**
     * @brief Destroys the Game object and its owned resources.
     */
    ~Game();

    //----------- Getters and Setters -----------

    /**
     * @brief Gets the current level.
     * @return Pointer to the current Level.
     */
    Level* getItsLevel() const;

    /**
     * @brief Sets a new level for the game.
     * @param newItsLevel Pointer to the new Level.
     */
    void setItsLevel(Level* newItsLevel);

    /**
     * @brief Gets the elapsed time since game start.
     * @return Elapsed time in milliseconds.
     */
    unsigned int getItsElapsedTime() const;

    /**
     * @brief Calculates and returns the player's score.
     * Writes score to a file.
     * @return Computed score as an unsigned integer.
     */
    unsigned int getItsScore();

    /**
     * @brief Writes the current score to a file and updates the leaderboard.
     */
    void writeFile();

private slots:
    /**
     * @brief Updates the entire model (players, enemies, spells, etc.).
     * Called by the timer every 8ms.
     */
    void updateModel();
};


#endif // GAME_H
