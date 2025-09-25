#ifndef PAUSEGUI_H
#define PAUSEGUI_H

#include <QWidget>


/**
 * @enum PauseType
 * @brief Represents the different options in the pause menu.
 *
 * Used to track which menu item is currently selected.
 */
enum PauseType
{
    RESUME,           ///< Continue the game.
    SETTINGINGAME,    ///< Open in-game settings.
    GOBACKTOMENU      ///< Return to the main menu.
};

/**
 * @class PauseGui
 * @brief GUI component that displays and manages the in-game pause menu.
 * @author A12
 * @version V2
 *
 * This widget renders the pause menu with selectable options,
 * allowing the player to resume the game, open settings, or go back to the main menu.
 */
class PauseGui : public QWidget
{
    Q_OBJECT

private:
    PauseType itsSelectedPauseType; ///< Currently selected pause menu option.

public:
    /**
     * @brief Constructs the PauseGui widget.
     * @param parent Pointer to parent widget.
     * @param aPauseType Initial selection (default is RESUME).
     */
    PauseGui(QWidget *parent = nullptr, PauseType aPauseType = RESUME);

    /**
     * @brief Paints the pause menu background and highlights the current selection.
     * @param event Paint event provided by Qt framework.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Updates the selected menu item based on navigation input.
     *
     * Direction values:
     * - 1 = Up key
     * - 2 = Down key
     * - 5 = Enter/Return key
     *
     * Emits the appropriate signal when an option is confirmed.
     *
     * @param aDirection Navigation input direction.
     */
    void updateSelectedMenu(int aDirection);

signals:
    /**
     * @brief Emitted when the user selects "Resume".
     */
    void SIG_RESUME();

    /**
     * @brief Emitted when the user selects "Settings".
     */
    void SIG_SETTINGINGAME();

    /**
     * @brief Emitted when the user selects "Go Back to Menu".
     */
    void SIG_GOBACKTOMENU();
};


#endif // PAUSEGUI_H
