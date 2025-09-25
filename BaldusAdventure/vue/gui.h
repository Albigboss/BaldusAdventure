#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QVBoxLayout>

#include "../controleur/game.h"
#include "menugui.h"
#include "levelgui.h"
#include "optiongui.h"
#include "pausegui.h"
#include "losenwingui.h"
#include "levelbonusgui.h"

#include "shopgui.h"


/**
 * @class GUI
 * @brief Main graphical user interface managing different game screens and input.
 *
 * The GUI class inherits from QWidget and serves as the main interface controller
 * for the game application. It manages multiple sub-GUI components such as the menu,
 * level display, shop, options, pause screen, and lose/win screen. It also handles
 * user input events like key presses and window resizing, as well as timer-driven
 * updates.
 *
 * Key features include:
 * - Switching between different game GUI components (menu, level, shop, etc.)
 * - Handling keyboard input for movement and spell casting
 * - Managing sound muting and layout resizing
 *
 * Signals are emitted for quitting, playing, and triggering sounds.
 *
 * @author A12
 * @version V2
 */
class GUI : public QWidget
{
    Q_OBJECT
private:
    Game *itsGame = nullptr; /**< Pointer to the current Game instance */
    MenuGUI *itsMenuGui = nullptr; /**< Pointer to the Menu GUI component */
    LevelGui *itsLevelGui = nullptr; /**< Pointer to the Level GUI component */
    ShopGui *itsShopGui = nullptr; /**< Pointer to the Shop GUI component */
    OptionGui *itsOptionGui = nullptr; /**< Pointer to the Options GUI component */
    PauseGui *itsPauseGui = nullptr; /**< Pointer to the Pause GUI component */
    LoseNWinGui *itsLoseNWinGui = nullptr; /**< Pointer to the Lose and Win GUI component */
    LevelBonusgui *itsLevelBonusgui = nullptr; /**< Pointer to the Level Bonus GUI component */
    QTimer *itsQTimer = nullptr; /**< Timer for periodic updates */
    QVBoxLayout* itsLayout = nullptr; /**< Layout manager for arranging widgets */

    Qt::Key itsSpellOneKey = Qt::Key_I; /**< Key binding for first spell */
    Qt::Key itsSpellTwoKey = Qt::Key_O; /**< Key binding for second spell */
    Qt::Key itsGoUpKey = Qt::Key_Up; /**< Key binding for moving up */
    Qt::Key itsGoLeftKey = Qt::Key_Left; /**< Key binding for moving left */
    Qt::Key itsGoRightKey = Qt::Key_Right; /**< Key binding for moving right */

    int itsStartingWidth; /**< Initial width of the GUI window */
    bool isSoundMuted = false; /**< Flag indicating if the sound is muted */

public:
    /**
     * @brief Constructor
     *
     * Initializes the GUI object and sets up the main interface.
     */
    GUI();

    /**
     * @brief Handles window resizing events.
     *
     * Called automatically when the window is resized to update layout and scaling.
     *
     * @param event Resize event containing new size information.
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief Handles key press events.
     *
     * Detects and processes key presses for game control, spell casting, and menu navigation.
     *
     * @param e Key event containing information about the pressed key.
     */
    void keyPressEvent(QKeyEvent* e) override;

    /**
     * @brief Handles key release events.
     *
     * Detects when keys are released to update game state accordingly.
     *
     * @param e Key event containing information about the released key.
     */
    void keyReleaseEvent(QKeyEvent* e) override;

    /**
     * @brief Returns a pointer to the Menu GUI component.
     *
     * @return Pointer to the MenuGUI instance.
     */
    MenuGUI *getItsMenuGui() const;

    /**
     * @brief Sets the current Game instance.
     *
     * @param newItsGame Pointer to the new Game instance.
     */
    void setItsGame(Game *newItsGame);

    /**
     * @brief Opens the in-game shop GUI.
     */
    void OpenShop();

    /**
     * @brief Slot triggered when the player enters the bonus door.
     */
    void onBonusDoor();

    /**
     * @brief Slot triggered when the player exits the bonus door.
     */
    void ExitBonusDoor();

public slots:
    /**
     * @brief Periodic update slot triggered by the timer.
     */
    void triggerUpdate();

    /**
     * @brief Slot called when the player selects to start the game.
     */
    void onSelectPlayGame();

    /**
     * @brief Slot called when the player selects the settings menu.
     */
    void onSelectSetting();

    /**
     * @brief Slot called when the player chooses to quit the game.
     */
    void onSelectQuit();

    /**
     * @brief Slot called when the options menu is closed.
     */
    void onCloseOptionMenu();

    /**
     * @brief Slot called when the player resumes the game from pause.
     */
    void onSelectResume();

    /**
     * @brief Slot called when the shop GUI is closed.
     */
    void onClosedShop();

signals:
    /**
     * @brief Signal emitted when the user requests to quit the game.
     */
    void SIG_QUIT();

    /**
     * @brief Signal emitted when the user requests to start playing the game.
     */
    void SIG_PLAY();

    /**
     * @brief Signal emitted to request playing specific sounds.
     *
     * 1-jump sound
     * 2-menu music
     * 4-level music
     * 5-gameover music
     * 6-gamewin music
     *
     * @param soundId Integer identifier for the sound to be played.
     */
    void SIG_SoundsToBePlayed(int soundId);
};


#endif // GUI_H
