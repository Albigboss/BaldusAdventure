#ifndef SHOPGUI_H
#define SHOPGUI_H

#include <QWidget>

/**
 * @enum ShopType
 * @brief Represents the different selectable elements within the shop GUI.
 */
enum ShopType
{
    SPELLUPLEFT,     ///< Top-left spell selection
    SPELLUPRIGHT,    ///< Top-right spell selection
    SPELLDOWNLEFT,   ///< Bottom-left spell selection
    SPELLDOWNRIGHT,  ///< Bottom-right spell selection
    WEAKPAGE,        ///< Switch to weak spells page
    AVERAGEPAGE,     ///< Switch to average spells page
    STRONGPAGE,      ///< Switch to strong spells page
    ESC              ///< Exit/close the shop
};

/**
 * @class ShopGui
 * @brief Widget that represents the in-game spell shop interface.
 * @author A12
 * @version V2
 *
 * Allows players to select and change spells, navigate through spell categories,
 * and rebind keys through a visual and interactive UI.
 */
class ShopGui : public QWidget
{
    Q_OBJECT
private:
    ShopType itscurrentSelection = SPELLUPLEFT; ///< Current selection in the shop.
    // Key bindings
    Qt::Key itsSpellOneKey = Qt::Key_I;         ///< Key bound to first spell.
    Qt::Key itsSpellTwoKey = Qt::Key_O;         ///< Key bound to second spell.
    Qt::Key itsGoUpKey = Qt::Key_Up;            ///< Key to navigate up.
    Qt::Key itsGoDownKey = Qt::Key_Down;        ///< Key to navigate down.
    Qt::Key itsReturnKey = Qt::Key_Return;      ///< Key to confirm.
    Qt::Key itsGoLeftKey = Qt::Key_Left;        ///< Key to navigate left.
    Qt::Key itsGoRightKey = Qt::Key_Right;      ///< Key to navigate right.

    bool isKeyChanging = false;                 ///< Whether a key is currently being remapped.
    int actualPage = 1;                         ///< Current page displayed (1=weak, 2=average, 3=strong).

public:
    /**
     * @brief Constructs the ShopGui widget.
     * @param parent Pointer to the parent QWidget.
     */
    ShopGui(QWidget *parent = nullptr);

    /**
     * @brief Paints the shop interface and highlights the selected element.
     * @param e The paint event.
     */
    void paintEvent(QPaintEvent *e) override;

    /**
     * @brief Updates the current selection based on a navigation direction.
     * @param aDirection Integer representing the direction (1=up, 2=down, 3=left, 4=right, 5=confirm).
     */
    void updateSelection(int aDirection);

    /**
     * @brief Sets the key-changing mode on or off.
     * @param newIsKeyChanging True to enable key remapping mode.
     */
    void setIsKeyChanging(bool newIsKeyChanging);

    /**
     * @brief Gets the currently active spell page.
     * @return An integer representing the page (1=weak, 2=average, 3=strong).
     */
    int getActualPage() const;

    /**
     * @brief Gets the currently selected shop element.
     * @return A ShopType enum value representing the selection.
     */
    ShopType getItscurrentSelection() const;

signals:
    /**
     * @brief Emitted when the player chooses to close the shop.
     */
    void SIG_SHOPCLOSE();
};


#endif // SHOPGUI_H
