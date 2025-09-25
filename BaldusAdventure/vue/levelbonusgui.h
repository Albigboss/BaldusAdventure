#ifndef LEVELBONUSGUI_H
#define LEVELBONUSGUI_H

#include "../controleur/game.h"
#include <QWidget>
#include "QPainter"

/**
 * @class LevelBonusgui
 * @brief Handles the graphical rendering of the bonus level.
 * @author A12
 * @version V2
 *
 * This class is responsible for rendering the bonus levels
 * of the game. It draws players, enemies, spells, obstacles, HUD, and bonus-specific
 * elements (ex : key, chest, exit door) based on the current game state. It also
 * adapts the display to window size by computing scaling ratios.
 */
class LevelBonusgui : public QWidget
{
    Q_OBJECT
private:
    Game *itsGame = nullptr;      ///< Pointer to the current Game instance.
    bool itsGameLose = false;     ///< Indicates if the player has lost the bonus level.
    int itsInitialWidth;          ///< Reference width used for scaling.
    int itsInitialHeight;         ///< Reference height used for scaling.
    double itsXRatio = 1.0;       ///< X-axis scaling ratio.
    double itsYRatio = 1.0;       ///< Y-axis scaling ratio.

public:
    /**
     * @brief Constructor for LevelBonusgui.
     * Initializes the widget and triggers bonus level initialization if players are present.
     * @param parent The parent QWidget.
     * @param aGame Pointer to the active Game instance.
     */
    LevelBonusgui(QWidget *parent, Game* aGame);

    /**
     * @brief Destructor.
     */
    ~LevelBonusgui();

    /**
     * @brief paintEvent override.
     * It draws all visible elements of the bonus level including
     * the HUD, players, enemies, spells, obstacles, and bonus-specific entities.
     * @param event Paint event trigger.
     * @see drawPlayer
     * @see drawEnemy
     * @see drawObstacle
     * @see drawSpell
     * @see drawHud
     * @see drawBonus
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Draws the player characters on the screen.
     * Renders each player with the appropriate sprite based on their direction.
     * @param aPainter QPainter instance used for drawing.
     */
    void drawPlayer(QPainter *aPainter);

    /**
     * @brief Draws all enemy entities.
     * Includes both regular enemies and shooter enemies, rendering their sprites
     * and projectiles if available.
     * @param aPainter QPainter instance used for drawing.
     */
    void drawEnemy(QPainter *aPainter);

    /**
     * @brief Draws all obstacles in the level.
     * Obstacles include walls, traps, and other types with different visual styles.
     * @param aPainter QPainter instance used for drawing.
     */
    void drawObstacle(QPainter *aPainter);

    /**
     * @brief Draws active spells cast by the players.
     * Displays both first and second spells using direction-based sprites if available.
     * @param aPainter QPainter instance used for drawing.
     */
    void drawSpell(QPainter *aPainter);

    /**
     * @brief Draws bonus-related elements.
     * Renders the key, chest using its sprite,
     * and the exit door.
     * @param aPainter QPainter instance used for drawing.
     */
    void drawBonus(QPainter *aPainter);

    /**
     * @brief Draws the game HUD (heads-up display).
     * Displays player coins and remaining hearts graphically.
     * @param aPainter QPainter instance used for drawing.
     */
    void drawHud(QPainter *aPainter);

    /**
     * @brief Returns whether the game is lost.
     * @return true if the player has lost the bonus level, false otherwise.
     */
    bool getItsGameLose() const;

    /**
     * @brief Sets the game lost state.
     * @param newItsGameLose New value for the game lose flag.
     */
    void setItsGameLose(bool newItsGameLose);
};


#endif // LEVELBONUSGUI_H
