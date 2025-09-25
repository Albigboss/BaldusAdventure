#include "maincontroller.h"


MainController::MainController()
    : QObject(nullptr),
    itsMusicPlayer(new QMediaPlayer(this)),
    itsSoundEffect(new QSoundEffect(this)),
    itsAudioOutput(new QAudioOutput(this))
{

    itsGui = new GUI();
    itsGui->show();
    connect(itsGui, SIGNAL(SIG_SoundsToBePlayed(int)), this, SLOT(soundToPlay(int)));

    itsMusicPlayer->setAudioOutput(itsAudioOutput);
    itsAudioOutput->setVolume(0.2);
    itsSoundEffect->setVolume(0);
    itsMusicPlayer->setLoops(QMediaPlayer::Infinite);

    soundToPlay(2);

    connect(itsGui, SIGNAL(SIG_PLAY()), this, SLOT(startGame()));
    connect(itsGui, SIGNAL(SIG_QUIT()), this, SLOT(quitGame()));
}

MainController::~MainController()
{
    delete itsGui;
    delete itsGame;

    delete itsSoundEffect;
    delete itsMusicPlayer;
    delete itsAudioOutput;
}

void MainController::startGame()
{
    //qDebug()<<"debut de start game";

    if(itsGame != nullptr)
    {
        delete itsGame;
        itsGame = nullptr;
    }

    itsGame = new Game;
    itsGui->setItsGame(itsGame);

    Player * aPlayer = itsGame->getItsLevel()->getItsPlayers()->front();
    connect(aPlayer, SIGNAL(SIG_SoundsToBePlayed(int)), this, SLOT(soundToPlay(int)));




    soundToPlay(4);




}

void MainController::quitGame()
{
    //qDebug()<<"on quitte le jeu";
    itsGui->hide();

    exit(0);
}

void MainController::soundToPlay(int aSoundCode)
{
    //"qrc:/sounds/sounds/jump.wav"

    if(aSoundCode == 0)
    {
        isSoundMuted?isSoundMuted = false:isSoundMuted = true;
        if(isSoundMuted)
        {
            itsAudioOutput->setMuted(true);
        }
        else
        {
            itsAudioOutput->setMuted(false);
        }
    }



    switch(aSoundCode)
    {
    case 0: break;
    case 1://saut
        if(!isSoundMuted)
        {
            itsSoundEffect->setSource(QUrl("qrc:/sounds/sounds/jump.wav"));
            itsSoundEffect->play();
        }
        break;//qrc:/sounds/sounds/jump.mp3
    case 2://musique dans le menu
        itsMusicPlayer->setSource(QUrl("qrc:/sounds/sounds/mainmenu.mp3"));
        itsMusicPlayer->play();
        break;
    case 4://musique niveau
        if(itsGame != nullptr and itsGame->getItsLevel() != nullptr and (itsGame->getItsLevel()->getItsLevelNumber() == 1))
        {
            itsMusicPlayer->setSource(QUrl("qrc:/sounds/sounds/horizontalLevels.mp3"));
            itsMusicPlayer->play();
        }
        else if(itsGame != nullptr and itsGame->getItsLevel() != nullptr and (itsGame->getItsLevel()->getItsLevelNumber()==3))
        {
            itsMusicPlayer->setSource(QUrl("qrc:/sounds/sounds/verticalLevels.mp3"));
            itsMusicPlayer->play();
        }
        break;
    case 5:
        itsMusicPlayer->setSource(QUrl("qrc:/sounds/sounds/gameOver.mp3"));
        itsMusicPlayer->play();
        break;
    case 6:
        itsMusicPlayer->setSource(QUrl("qrc:/sounds/sounds/gameWin.mp3"));
        itsMusicPlayer->play();
        break;
    default:
        return ;
    }


}
