#ifndef LEVELGUI_H
#define LEVELGUI_H
#include <QPainter>
#include <QWidget>
#include "../controleur/game.h"

/**
 * @class LevelGui
 * @brief Widget that displays the current game level, including players, enemies, obstacles, and HUD.
 *
 * The LevelGui class inherits from QWidget and is responsible for rendering
 * the entire level view in the game window. It manages drawing the background,
 * the player(s), enemies, obstacles, spells, doors, and the HUD overlay.
 * It also handles view translation to follow the player position,
 * scaling for window resizing, and detecting game loss state.
 *
 * @author A12
 * @version V2
 */
class LevelGui : public QWidget
{
    Q_OBJECT

private:
    Game *itsGame = nullptr; /**< Pointer to the current Game instance providing level data */
    bool itsGameLose = false; /**< Flag indicating if the game is lost */
    double itsXRatio = 1.0; /**< Horizontal scaling factor based on window resize */
    double itsYRatio = 1.0; /**< Vertical scaling factor based on window resize */
    int itsInitialWidth; /**< Initial width of the widget for scaling calculations */
    int itsInitialHeight; /**< Initial height of the widget for scaling calculations */
    QPixmap *itsQPixmap = nullptr; /**< Background pixmap of the current level */
    QPixmap *itsHudHeartOnePixmap = new QPixmap(":/hud/images/hud/hud-heart-1.png"); /**< HUD image for one heart */
    QPixmap *itsHudHeartTwoPixmap = new QPixmap(":/hud/images/hud/hud-heart-2.png"); /**< HUD image for two hearts */
    QPixmap *itsHudHeartThreePixmap = new QPixmap(":/hud/images/hud/hud-heart-3.png"); /**< HUD image for three hearts */
    QPixmap *itsPieceHudPixmap = new QPixmap(":/hud/images/hud/Hud-piece.png"); /**< HUD image for collected pieces */
    QRect itsDrawingArea; /**< Rectangle defining the visible drawing area of the level */

public:
    /**
     * @brief Constructor
     *
     * Initializes the LevelGui widget with an optional parent and associated Game pointer.
     * It loads and initializes the current level and its background.
     *
     * @param parent Parent widget, default nullptr.
     * @param aGame Pointer to the Game instance to access game data.
     */
    LevelGui(QWidget *parent = nullptr, Game *aGame = nullptr);

    /**
     * @brief Destructor.
     */
    ~LevelGui();

    /**
     * @brief Overridden paint event to render the level.
     *
     * Handles drawing the background, game entities (players, enemies, obstacles),
     * spells, doors, and the HUD. Also manages view translation and scaling.
     *
     * @param event Paint event parameters.
     * @see drawPlayer(QPainter*)
     * @see drawEnemy(QPainter*)
     * @see drawObstacle(QPainter*)
     * @see drawHud(QPainter *aPainter)
     * @see drawSpell(QPainter *aPainter)
     * @see drawDoor(QPainter *aPainter)
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Draws the player(s) on the widget.
     *
     * @param aPainter Pointer to the QPainter used for drawing.
     */
    void drawPlayer(QPainter *aPainter);

    /**
     * @brief Draws all enemies in the level.
     *
     * @param aPainter Pointer to the QPainter used for drawing.
     */
    void drawEnemy(QPainter *aPainter);

    /**
     * @brief Draws all obstacles in the level.
     *
     * @param aPainter Pointer to the QPainter used for drawing.
     */
    void drawObstacle(QPainter *aPainter);

    /**
     * @brief Draws spells currently active in the level.
     *
     * @param aPainter Pointer to the QPainter used for drawing.
     */
    void drawSpell(QPainter *aPainter);

    /**
     * @brief Draws doors present in the level.
     *
     * @param aPainter Pointer to the QPainter used for drawing.
     */
    void drawDoor(QPainter *aPainter);

    /**
     * @brief Draws the HUD (health, pieces, etc.) overlay on the widget.
     *
     * @param aPainter Pointer to the QPainter used for drawing.
     */
    void drawHud(QPainter *aPainter);

    /**
     * @brief Sets the game lose state.
     *
     * @param newItsGameLose True if the game is lost, false otherwise.
     */
    void setItsGameLose(bool newItsGameLose);

    /**
     * @brief Returns whether the game is lost.
     *
     * @return true if the game is lost, false otherwise.
     */
    bool getItsGameLose() const;

    /**
     * @brief Calculates and sets the scaling coefficients based on widget size.
     */
    void setItsResizeCoef();

    /**
     * @brief Sets the background pixmap.
     *
     * @param newItsQPixmap Pointer to the new background QPixmap.
     */
    void setItsQPixmap(QPixmap *newItsQPixmap);

    /**
     * @brief Returns the current background pixmap.
     *
     * @return Pointer to the current background QPixmap.
     */
    QPixmap *getItsQPixmap() const;
};

#endif // LEVELGUI_H
