#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "controleur/game.h"
#include "vue/gui.h"

#include <QObject>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QAudioOutput>



/**
 * @class MainController
 * @brief Handles the core logic and audio control of the game.
 * The MainController manages the GUI, game lifecycle, and all sound/music playback.
 * It acts as the central communication hub between the game model and the GUI.
 * @author A12
 * @version V2
 */
class MainController : public QObject
{
    Q_OBJECT

private:
    GUI *itsGui = nullptr;                    ///< Pointer to the main GUI.
    Game *itsGame = nullptr;                  ///< Pointer to the Game.
    QMediaPlayer *itsMusicPlayer = nullptr;   ///< Handles music playback.
    QSoundEffect *itsSoundEffect = nullptr;   ///< Handles short sound effects.
    QAudioOutput *itsAudioOutput = nullptr;   ///< Controls audio output volume and mute.
    bool isSoundMuted = false;                ///< Flag indicating if sound is muted.

public:
    /**
     * @brief Constructs the MainController.
     * Initializes the GUI, music/sound components, and connects signals/slots.
     */
    MainController();
    ~MainController();

private slots:
    /**
     * @brief Starts a new game.
     * Initializes a new Game instance and connects player sound signals.
     */
    void startGame();

    /**
     * @brief Quits the game application.
     * Hides the GUI and exits the program.
     */
    void quitGame();

    /**
     * @brief Triggers sound or music playback based on an input code.
     * Handles menu music, in-game music, sound effects like jumping or shooting,
     * toggles mute, and plays win/lose music based on the code provided.
     * @param aSoundCode Integer representing the sound or music to play.
     */
    void soundToPlay(int aSoundCode);
};


#endif // MAINCONTROLLER_H
