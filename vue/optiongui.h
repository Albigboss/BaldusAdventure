#ifndef OPTIONGUI_H
#define OPTIONGUI_H

#include <QWidget>
#include <QPainter>
#include <QRect>

/**
 * @enum SettingType
 * @brief Defines the configurable options in the settings menu.
 *
 * Used to identify which setting is currently selected or being modified.
 */
enum SettingType
{
    SPELL1, ///< Primary spell key binding.
    SPELL2, ///< Secondary spell key binding.
    UP,     ///< Move up key binding.
    LEFT,   ///< Move left key binding.
    RIGHT,  ///< Move right key binding.
    BACK,   ///< Go back/exit settings menu.
    SOUND   ///< Toggle sound mute/unmute.
};



/**
 * @class OptionGui
 * @brief GUI for configuring key bindings and sound settings in-game.
 *
 * Allows the user to change control keys for spells and movement,
 * toggle sound, and return to the previous menu.
 */
class OptionGui : public QWidget
{
    Q_OBJECT

private:
    SettingType itscurrentSetting; ///< Currently selected setting.
    Qt::Key itsSpellOneKey = Qt::Key_I; ///< Bound key for primary spell.
    Qt::Key itsSpellTwoKey = Qt::Key_O; ///< Bound key for secondary spell.
    Qt::Key itsGoUpKey = Qt::Key_Up; ///< Bound key for upward movement.
    Qt::Key itsGoLeftKey = Qt::Key_Left; ///< Bound key for leftward movement.
    Qt::Key itsGoRightKey = Qt::Key_Right; ///< Bound key for rightward movement.
    bool isKeyChanging = false; ///< Whether the user is currently reassigning a key.
    bool isSoundMuted = false; ///< Indicates if the sound is currently muted.

public:
    /**
     * @brief Constructor for OptionGui.
     * @param parent Parent widget.
     * @param aSetting Initial setting to highlight.
     * @param aSoundMuted Initial mute state.
     */
    OptionGui(QWidget *parent = nullptr, SettingType aSetting = SPELL1, bool aSoundMuted = false);

    /**
     * @brief Renders the settings menu and highlights the current option.
     * @param e Qt paint event.
     */
    void paintEvent(QPaintEvent *e) override;

    /**
     * @brief Navigates the menu or triggers actions.
     *
     * Accepted directions:
     * - 1: Move up
     * - 2: Move down
     * - 3: Move left
     * - 4: Move right
     * - 5: Enter/select
     *
     * @param aDirection The direction/action to process.
     */
    void updateSetting(int aDirection);

    /**
     * @brief Draws the current key bindings on the screen.
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawKeys(QPainter *aPainter = nullptr);

    /**
     * @brief Sets all key bindings at once.
     */
    void setKeys(Qt::Key aSpellOneKey = Qt::Key_I,
                 Qt::Key aSpellTwoKey = Qt::Key_O,
                 Qt::Key aGoUpKey = Qt::Key_Up,
                 Qt::Key aGoLeftKey = Qt::Key_Left,
                 Qt::Key aGoRightKey = Qt::Key_Right);

    /**
     * @brief Returns whether the user is currently changing a key.
     */
    bool getIsKeyChanging() const;

    /**
     * @brief Sets the key-changing state.
     * @param newIsKeyChanging True if user is changing a key, false otherwise.
     */
    void setIsKeyChanging(bool newIsKeyChanging);

    /**
     * @brief Updates a single key binding based on the selected setting.
     * @param aSetting The setting to change.
     * @param aKey The new key to bind.
     */
    void setOneKey(SettingType aSetting, Qt::Key aKey);

    /**
     * @brief Returns the currently selected setting.
     */
    SettingType getItscurrentSetting() const;

signals:
    /**
     * @brief Emitted when the user chooses to exit the options menu.
     */
    void SIG_OPTIONCLOSE();

    /**
     * @brief Emitted when the user toggles the sound mute setting.
     */
    void SIG_MUTESOUND();
};


#endif // OPTIONGUI_H
