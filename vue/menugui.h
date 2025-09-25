#ifndef MENUGUI_H
#define MENUGUI_H


#include <QWidget>
#include <QRect>
#include <QPainter>

/**
 * @brief The MenuType enum
 * It is used to know which menu is selected
 */
enum MenuType
{
    PLAY,
    SETTING,
    QUIT
};

/**
 * @brief The MenuGUI class
 * It is used to display the menu which is launched when the game is started. One in it, you can start the game,
 * go to the settings or quit the game.
 * @author A12
 * @version 1
 *
 */
class MenuGUI : public QWidget
{
    Q_OBJECT
private:
    MenuType itsSelectedMenu;
public:
    /**
     * @brief MenuGUI is the constructor fo the class MenuGUI
     * @param parent used to se the parent widget
     * @param aMenuType used if we want to start the game from a certain slected menu in a later version
     */
    MenuGUI(QWidget *parent = nullptr, MenuType aMenuType = PLAY);
    /**
     * @brief paintEvent is a overload method to draw the menu
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;
    /**
     * @brief updateQRect is called when the arrows are pressed to change the selected menu
     * @param aDirection 1 = key_Up, 2 = Key_Down, 5 = Key_Return
     */
    void updateSelectedMenu(int aDirection);
    ~MenuGUI();
signals:
    /**
     * @brief SIG_PLAYGAME is sent when the Return key is pressed and the PLAY MenuType is selected
     * @see MenuType
     */
    void SIG_PLAYGAME();
    /**
     * @brief SIG_SETTING is sent when the Return key is pressed and the SETTING MenuType is selected
     * @see MenuType
     */
    void SIG_SETTING();
    /**
     * @brief SIG_QUIT is sent when the Return key is pressed and the QUIT MenuType is selected
     * @see MenuType
     */
    void SIG_QUIT();
};
#endif // MENUGUI_H
