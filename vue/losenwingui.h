#ifndef LOSENWINGUI_H
#define LOSENWINGUI_H

#include <QWidget>
#include <QPixmap>


/**
 * @class LoseNWinGui
 * @brief A QWidget subclass to display win or lose screen with the final score.
 *
 * This GUI widget shows either a winning or losing image and displays the player's final score.
 * The images can be customized via constructor parameters.
 *
 * @author A12
 * @version 2
 */
class LoseNWinGui : public QWidget
{
    Q_OBJECT
private:
    QPixmap itsWinPixMap;   ///< Pixmap to display when the game is won.
    QPixmap itsLosePixmap;  ///< Pixmap to display when the game is lost.
    bool itsGameWon;        ///< True if the game was won, false otherwise.
    int itsScore;           ///< The player's final score to display.
    int itsTime;              ///< The player's time at the end of the game
public:
    /**
     * @brief Constructor for LoseNWinGui.
     *
     * @param parent Parent widget.
     * @param aGameWon Boolean flag indicating if the game was won.
     * @param aScore The player's final score.
     * @param aWinPixmap Pixmap for the win screen image (default is a predefined resource).
     * @param aLosePixmap Pixmap for the lose screen image (default is a predefined resource).
     */
    LoseNWinGui(QWidget *parent, bool aGameWon, int aScore, int aTime, QPixmap aWinPixmap = QString::fromStdString(":/menu/images/menus/menuWin.png"), QPixmap aLosePixmap = QString::fromStdString(":/menu/images/menus/menuMort.png"));

    /**
     * @brief Paint event handler to draw the win/lose image and score text.
     *
     * @param event Paint event.
     */
    void paintEvent(QPaintEvent *event) override;
};


#endif // LOSENWINGUI_H
