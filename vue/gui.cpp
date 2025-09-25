#include "gui.h"
#include <QDebug>
#include "controleur/EnnemyType/skeleton.h"

#include <QVBoxLayout>
#include <QKeyEvent>


MenuGUI *GUI::getItsMenuGui() const
{
    return itsMenuGui;
}

GUI::GUI() : QWidget(nullptr)
{
    setMinimumSize(1024,576);
    itsStartingWidth = width();

    itsMenuGui = new MenuGUI(this);

    // QVBoxLayout *layout = new QVBoxLayout(this);
    // layout->addWidget(itsMenuGui);


    itsLayout = new QVBoxLayout(this);
    itsLayout->addWidget(itsMenuGui);

    itsMenuGui->show();
    //this->setWindowState(Qt::WindowFullScreen);


    itsQTimer = new QTimer(this);
    connect(itsQTimer, SIGNAL(timeout()), this, SLOT(triggerUpdate()));
    itsQTimer->start(17);
    //qDebug()<<"Thread Gui  : "<<itsQTimer->thread();


    connect(itsMenuGui, SIGNAL(SIG_PLAYGAME()), this, SLOT(onSelectPlayGame()));
    connect(itsMenuGui, SIGNAL(SIG_SETTING()), this, SLOT(onSelectSetting()));
    connect(itsMenuGui, SIGNAL(SIG_QUIT()), this, SLOT(onSelectQuit()));
    setLayout(itsLayout);

}


void GUI::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Récupérer les dimensions actuelles de la fenêtre
    int currentWidth = width();
    int currentHeight = height();

    // Ratio d'aspect (ici 16:9)
    float aspectRatio = 16.0f / 9.0f;

    // Calculer les nouvelles dimensions en fonction du ratio d'aspect
    if (currentWidth / aspectRatio < currentHeight) {
        // Si la largeur relative est plus grande que la hauteur, ajuster la hauteur
        int newHeight = currentWidth / aspectRatio;
        resize(currentWidth, newHeight);  // Garder la largeur et ajuster la hauteur
    } else {
        // Sinon, ajuster la largeur
        int newWidth = currentHeight * aspectRatio;
        resize(newWidth, currentHeight);  // Garder la hauteur et ajuster la largeur
    }

    currentWidth = width();
    currentHeight = height();
}




void GUI::keyPressEvent(QKeyEvent *e)
{
    //appeler setKeys

    if(itsLevelGui != nullptr and itsOptionGui == nullptr and itsPauseGui == nullptr and e->key() == Qt::Key_Escape and itsShopGui==nullptr)
    {
        itsGame->itsQTimer->stop();

        //emettre un signal pour dire de stopper la mise à jour du jeu
        itsPauseGui = new PauseGui(this);


        itsLayout->addWidget(itsPauseGui);
        itsLevelGui->hide();
        itsPauseGui->show();
        connect(this->itsPauseGui, SIGNAL(SIG_RESUME()), this, SLOT(onSelectResume()));
        connect(this->itsPauseGui, SIGNAL(SIG_SETTINGINGAME()), this, SLOT(onSelectSetting()));
        connect(this->itsPauseGui, SIGNAL(SIG_GOBACKTOMENU()), this, SLOT(onSelectQuit()));
    }
    else if(itsLevelBonusgui != nullptr and itsOptionGui == nullptr and itsPauseGui == nullptr and e->key() == Qt::Key_Escape and itsShopGui==nullptr)
    {
        itsGame->itsQTimer->stop();

        //emettre un signal pour dire de stopper la mise à jour du jeu
        itsPauseGui = new PauseGui(this);


        itsLayout->addWidget(itsPauseGui);
        itsLevelBonusgui->hide();
        itsPauseGui->show();
        connect(this->itsPauseGui, SIGNAL(SIG_RESUME()), this, SLOT(onSelectResume()));
        connect(this->itsPauseGui, SIGNAL(SIG_SETTINGINGAME()), this, SLOT(onSelectSetting()));
        connect(this->itsPauseGui, SIGNAL(SIG_GOBACKTOMENU()), this, SLOT(onSelectQuit()));
    }


    if(itsOptionGui != nullptr and itsOptionGui->getIsKeyChanging())
    {
        ////qDebug()<<"on change la clé";
        itsOptionGui->setOneKey(itsOptionGui->getItscurrentSetting(), e->keyCombination().key());
        //itsSpellOneKey = itsOptionGui.get
        switch (itsOptionGui->getItscurrentSetting()) {
        case SPELL1:
            itsSpellOneKey = e->keyCombination().key();
            break;
        case SPELL2:
            itsSpellTwoKey = e->keyCombination().key();
            break;
        case UP:
            itsGoUpKey = e->keyCombination().key();
            break;
        case LEFT:
            itsGoLeftKey = e->keyCombination().key();
            break;
        case RIGHT:
            itsGoRightKey = e->keyCombination().key();
            break;
        default:
            break;
        }

        return ;
    }


    if (e->key() == itsGoLeftKey)
    {
        ////qDebug()<<"touche gauche pressée";
        if(itsLevelGui != nullptr or itsLevelBonusgui != nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                p->setItsLeft(true);
            }
        }
    }
    if(e->key() == Qt::Key_Left)
    {
        if(itsOptionGui != nullptr)
        {
            itsOptionGui->updateSetting(3);
        }
        else if(itsShopGui != nullptr)
        {
            itsShopGui->updateSelection(3);
        }
    }


    if (e->key() == itsGoRightKey)
    {
        ////qDebug()<<"touche droite pressée";
        if(itsLevelGui != nullptr or itsLevelBonusgui != nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                p->setItsRight(true);
            }
        }

    }
    if(e->key() == Qt::Key_Right)
    {
        if(itsOptionGui != nullptr)
        {

            itsOptionGui->updateSetting(4);
        }
        else if(itsShopGui != nullptr)
        {
            itsShopGui->updateSelection(4);
        }
    }

    if(e->key() == itsGoUpKey)
    {
        ////qDebug()<<"touche haut pressée";
        if((itsLevelGui != nullptr or itsLevelBonusgui != nullptr) and itsOptionGui == nullptr and itsPauseGui == nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {

                p->jump();
            }
            if (itsGame->getItsLevel()->getItsDoor() != nullptr)
            {
                itsGame->getItsLevel()->getItsDoor()->OpenDoor(itsGame->getItsLevel()->getItsPlayers());
                if (itsGame->getItsLevel()->getItsDoor()->getInDoor() == true)
                {
                    onBonusDoor();
                }
            }
            if (itsGame->getItsLevel()->getItsDoorExit() != nullptr)
            {
                itsGame->getItsLevel()->getItsDoorExit()->OpenDoor(itsGame->getItsLevel()->getItsPlayers());
                if (itsGame->getItsLevel()->getItsDoorExit()->getInDoor() == true)
                {
                    ExitBonusDoor();
                }
            }
        }
    }
    if(e->key() == Qt::Key_Up)
    {
        if(itsMenuGui != nullptr)
        {
            itsMenuGui->updateSelectedMenu(1);
        }
        else if(itsOptionGui != nullptr)
        {
            itsOptionGui->updateSetting(1);
        }
        else if(itsPauseGui != nullptr)
        {
            itsPauseGui->updateSelectedMenu(1);
        }
        else if(itsShopGui != nullptr)
        {
            itsShopGui->updateSelection(1);
        }
    }

    if(e->key() == Qt::Key_Down)
    {
        ////qDebug()<<"touche bas pressée";
        if(itsMenuGui != nullptr)
        {
            itsMenuGui->updateSelectedMenu(2);
        }
        else if(itsOptionGui != nullptr)
        {
            itsOptionGui->updateSetting(2);
        }
        else if(itsPauseGui != nullptr)
        {
            itsPauseGui->updateSelectedMenu(2);
        }
        else if(itsShopGui != nullptr)
        {
            itsShopGui->updateSelection(2);
        }

    }

    if(e->key() == Qt::Key_Return)
    {
        if(itsMenuGui != nullptr)
        {
            itsMenuGui->updateSelectedMenu(5);

        }
        else if(itsOptionGui != nullptr)
        {
            itsOptionGui->updateSetting(5);
        }
        else if(itsPauseGui != nullptr)
        {
            itsPauseGui->updateSelectedMenu(5);
        }
        else if(itsShopGui != nullptr)
        {
            itsShopGui->updateSelection(5);
        }
        else if(itsLoseNWinGui != nullptr)
        {
            itsLoseNWinGui->hide();
            delete itsLoseNWinGui;
            itsLoseNWinGui = nullptr;

            itsMenuGui = new MenuGUI(this);
            itsLayout->addWidget(itsMenuGui);
            itsMenuGui->show();
            emit SIG_SoundsToBePlayed(2);

            connect(itsMenuGui, SIGNAL(SIG_PLAYGAME()), this, SLOT(onSelectPlayGame()));
            connect(itsMenuGui, SIGNAL(SIG_SETTING()), this, SLOT(onSelectSetting()));
            connect(itsMenuGui, SIGNAL(SIG_QUIT()), this, SLOT(onSelectQuit()));
        }
    }

    if(e->key() == itsSpellOneKey)
    {
        if(itsLevelGui != nullptr and itsGame->getItsLevel()->getItsShop() != nullptr and  itsGame->getItsLevel()->getItsShop()->canOpenShop(*itsGame->getItsLevel()->getItsPlayers()) and  itsShopGui == nullptr)
        {
            OpenShop();
            return;
        }
        if((itsLevelGui != nullptr or itsLevelBonusgui != nullptr) && itsShopGui == nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                if(itsGame->getItsLevel()->getCanThrowFirstSpell() == true)
                {
                    p->setIsFirstSpell(true);
                    itsGame->getItsLevel()->setCanThrowFirstSpell(false);
                    p->itsFirstSpellcoolDown->start(p->getItsFirstSpell()->getItsReloadTime());

                    if(p->getItsFirstSpell()->getIsProjectileSpell())
                    {
                        p->getItsFirstSpell()->setItsDirection(p->getItsDirection());
                        p->getItsFirstSpell()->setItsMaxDistance(p->getItsShape()->center().x()+p->getItsFirstSpell()->getItsRange());

                        p->getItsFirstSpell()->setItsEntitie(new Entities(p->getItsShape()->center().x() - (p->getItsFirstSpell()->getItsPixMap()->front().width()/2)*4,
                                                                          p->getItsShape()->center().y() - (p->getItsFirstSpell()->getItsPixMap()->front().height()/2)*4,
                                                                          new QRect(p->getItsShape()->center().x() - (p->getItsFirstSpell()->getItsPixMap()->front().width()/2)*4,
                                                                                    p->getItsShape()->center().y() - (p->getItsFirstSpell()->getItsPixMap()->front().height()/2)*4,
                                                                                    p->getItsFirstSpell()->getItsPixMap()->front().width()*4,
                                                                                    p->getItsFirstSpell()->getItsPixMap()->front().height()*4)));

                        p->getItsFirstSpell()->getItsEntitie()->setItsPixMap(p->getItsFirstSpell()->getItsPixMap());
                    }
                    else{
                        p->getItsFirstSpell()->setItsDirection(p->getItsDirection());
                        p->getItsFirstSpell()->setItsEntitie(new Entities(p->getItsX(), p->getItsY(), new QRect(p->getItsX(), p->getItsY(), p->getItsFirstSpell()->getItsPixMap()->front().width()*4, p->getItsFirstSpell()->getItsPixMap()->front().height()*4)));
                        p->getItsFirstSpell()->getItsEntitie()->setItsPixMap(p->getItsFirstSpell()->getItsPixMap());
                    }
                }
            }
            
        }
        if(itsShopGui != nullptr)
        {
            itsShopGui->setIsKeyChanging(false);
            itsGame->getItsLevel()->getItsShop()->selectSpellOne(itsShopGui->getActualPage(), itsShopGui->getItscurrentSelection());
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                p->setItsFirstSpell(itsGame->getItsLevel()->getItsShop()->getItsFirstSelectedSpell());
            }
        }

    }
    if(e->key() == itsSpellTwoKey )
    {
        
        ////qDebug()<<"touche sort 2 pressée";
        if(itsLevelGui != nullptr and itsGame->getItsLevel()->getItsShop() != nullptr and itsGame->getItsLevel()->getItsShop()->canOpenShop(*itsGame->getItsLevel()->getItsPlayers()) and itsShopGui == nullptr)
        {
            OpenShop();
            return;
        }
        if((itsLevelGui != nullptr or itsLevelBonusgui != nullptr) && itsShopGui==nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                if(itsGame->getItsLevel()->getCanThrowSecondSpell() == true)
                {
                    p->setIsSecondSpell(true);
                    itsGame->getItsLevel()->setCanThrowSecondSpell(false);
                    p->itsSecondSpellcoolDown->start(p->getItsSecondSpell()->getItsReloadTime());

                    if(p->getItsSecondSpell()->getIsProjectileSpell())
                    {
                        p->getItsSecondSpell()->setItsDirection(p->getItsDirection());
                        p->getItsSecondSpell()->setItsMaxDistance(p->getItsShape()->center().x()+p->getItsSecondSpell()->getItsRange());

                        p->getItsSecondSpell()->setItsEntitie(new Entities(p->getItsShape()->center().x() - (p->getItsSecondSpell()->getItsPixMap()->front().width()/2)*4,
                                                                          p->getItsShape()->center().y() - (p->getItsSecondSpell()->getItsPixMap()->front().height()/2)*4,
                                                                          new QRect(p->getItsShape()->center().x() - (p->getItsSecondSpell()->getItsPixMap()->front().width()/2)*4,
                                                                                    p->getItsShape()->center().y() - (p->getItsSecondSpell()->getItsPixMap()->front().height()/2)*4,
                                                                                    p->getItsSecondSpell()->getItsPixMap()->front().width()*4,
                                                                                    p->getItsSecondSpell()->getItsPixMap()->front().height()*4)));

                        p->getItsSecondSpell()->getItsEntitie()->setItsPixMap(p->getItsSecondSpell()->getItsPixMap());
                    }
                    else{
                        p->getItsSecondSpell()->setItsDirection(p->getItsDirection());
                        p->getItsSecondSpell()->setItsEntitie(new Entities(p->getItsX(), p->getItsY(), new QRect(p->getItsX(), p->getItsY(), p->getItsSecondSpell()->getItsPixMap()->front().width()*4, p->getItsSecondSpell()->getItsPixMap()->front().height()*4)));
                        p->getItsSecondSpell()->getItsEntitie()->setItsPixMap(p->getItsSecondSpell()->getItsPixMap());
                    }
                }
            }
        }
        if(itsShopGui != nullptr)
        {
            itsShopGui->setIsKeyChanging(false);
            itsGame->getItsLevel()->getItsShop()->selectSpellTwo(itsShopGui->getActualPage(), itsShopGui->getItscurrentSelection());
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                p->setItsSecondSpell(itsGame->getItsLevel()->getItsShop()->getItsSecondSelectedSpell());
            }
        }
    }

}

void GUI::keyReleaseEvent(QKeyEvent *e)
{

    if (e->key() == itsGoLeftKey)
    {
        if(itsLevelGui != nullptr or itsLevelBonusgui != nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                p->setItsLeft(false);
            }
        }
    }


    if (e->key() == itsGoRightKey)
    {
        if(itsLevelGui != nullptr or itsLevelBonusgui != nullptr)
        {
            for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
            {
                p->setItsRight(false);
            }
        }
    }
}

void GUI::triggerUpdate()
{
    //qDebug()<<"debut de trigger update ";

    if(itsLevelGui != nullptr)// and itsLevelGui->getItsQPixmap()->isNull())
    {
        //qDebug()<<"dans le if";
        itsLevelGui->setItsQPixmap(itsGame->getItsLevel()->getItsBackground());
    }

    //qDebug()<<"debut de update";
    update();
    //qDebug()<<"fin de update";

    if(itsLevelGui != nullptr and itsLevelGui->getItsGameLose())
    {
        //lancer le signal pour stopper les timers du modèle
        itsGame->itsQTimer->stop();
        itsLoseNWinGui = new LoseNWinGui(this, 0, itsGame->getItsScore(), itsGame->getItsElapsedTime());
        itsLayout->addWidget(itsLoseNWinGui);

        itsLevelGui->hide();
        itsLoseNWinGui->show();
        emit SIG_SoundsToBePlayed(5);

        delete itsLevelGui;
        itsLevelGui = nullptr;
    }
    else if (itsLevelBonusgui != nullptr and itsLevelBonusgui->getItsGameLose())
    {
        //lancer le signal pour stopper les timers du modèle
        itsGame->itsQTimer->stop();
        itsLoseNWinGui = new LoseNWinGui(this, 0, itsGame->getItsScore(),itsGame->getItsElapsedTime());
        itsLayout->addWidget(itsLoseNWinGui);

        itsLevelBonusgui->hide();
        itsLoseNWinGui->show();
        emit SIG_SoundsToBePlayed(5);

        delete itsLevelBonusgui;
        itsLevelBonusgui = nullptr;
    }
    else if(itsLevelGui != nullptr and
            itsGame->getItsLevel()->getItsPlayers()->front()->getItsShape()->center().x() > itsGame->getItsLevel()->getItsLevelWidth()-50 and
               itsGame->getItsLevel()->getItsLevelNumber() == 1)
    {
        itsGame->getItsLevel()->resetLevel();
        itsGame->getItsLevel()->initLevelThree();
        itsLevelGui->setItsQPixmap(itsGame->getItsLevel()->getItsBackground());
        emit SIG_SoundsToBePlayed(4);
    }
    else if(itsLevelGui != nullptr and
               itsGame->getItsLevel()->getItsPlayers()->front()->getItsShape()->center().y() < 1450 and itsGame->getItsLevel()->getItsLevelNumber() == 3)
    {
        itsGame->getItsLevel()->resetLevel();
        itsGame->getItsLevel()->initLevelFour();
        itsLevelGui->setItsQPixmap(itsGame->getItsLevel()->getItsBackground());
        emit SIG_SoundsToBePlayed(4);
    }
    else if(itsLevelGui != nullptr and itsGame->getItsLevel()->getItsPlayers()->front()->getItsShape()->center().y() < 1450 and itsGame->getItsLevel()->getItsLevelNumber() == 4)
    {
        //lancer le signal pour stopper les timers du modèle
        itsGame->itsQTimer->stop();
        itsLoseNWinGui = new LoseNWinGui(this, 1, itsGame->getItsScore(), itsGame->getItsElapsedTime());
        itsLayout->addWidget(itsLoseNWinGui);

        itsLevelGui->hide();
        itsLoseNWinGui->show();
        emit SIG_SoundsToBePlayed(6);

        delete itsLevelGui;
        itsLevelGui = nullptr;
    }
    //qDebug()<<"fin de triggerupdate";
}


void GUI::onSelectPlayGame()
{
    //qDebug()<<"debut de select playgame";

    itsMenuGui->hide();

    emit SIG_PLAY();

    //qDebug()<<itsGame;
    itsLevelGui = new LevelGui(this, itsGame);
    //qDebug()<<itsGame<<" après le levelGui";
    itsLayout->addWidget(itsLevelGui);
    itsLevelGui->show();


    delete itsMenuGui;
    itsMenuGui = nullptr;
    //qDebug()<<"fin de select playgame";

}

void GUI::onSelectSetting()
{

    itsOptionGui = new OptionGui(this,SPELL1,isSoundMuted);
    itsOptionGui->setKeys(itsSpellOneKey,
                          itsSpellTwoKey,
                          itsGoUpKey,
                          itsGoLeftKey,
                          itsGoRightKey);

    connect(itsOptionGui, SIGNAL(SIG_OPTIONCLOSE()), this, SLOT(onCloseOptionMenu()));
    connect(itsOptionGui, &OptionGui::SIG_MUTESOUND, this, [this]() {
        isSoundMuted? isSoundMuted = false: isSoundMuted = true;
        emit SIG_SoundsToBePlayed(0);
    });


    itsLayout->addWidget(itsOptionGui);

    if(itsMenuGui != nullptr)//We are in the main menu
    {
        itsMenuGui->hide();
        delete itsMenuGui;
        itsMenuGui = nullptr;
    }
    else if(itsPauseGui != nullptr)//We are in the pause menu (in game)
    {
        itsPauseGui->hide();
        delete itsPauseGui;
        itsPauseGui = nullptr;
    }

    itsOptionGui->show();
    //qDebug()<<"fin de select setting";

}

void GUI::onSelectQuit()
{


    //qDebug()<<"debut de select quit";


    if(itsLevelGui != nullptr)
    {
        itsMenuGui = new MenuGUI(this);
        itsLayout->addWidget(itsMenuGui);

        connect(itsMenuGui, SIGNAL(SIG_PLAYGAME()), this, SLOT(onSelectPlayGame()));
        connect(itsMenuGui, SIGNAL(SIG_SETTING()), this, SLOT(onSelectSetting()));
        connect(itsMenuGui, SIGNAL(SIG_QUIT()), this, SLOT(onSelectQuit()));

        itsPauseGui->hide();
        delete itsPauseGui;
        itsPauseGui = nullptr;

        delete itsLevelGui;
        itsLevelGui = nullptr;
        //envoyer un signal pour stopper la mise a jour du modèle

        itsMenuGui->show();
        emit SIG_SoundsToBePlayed(2);
    }
    else if(itsLevelBonusgui != nullptr){
        itsMenuGui = new MenuGUI(this);
        itsLayout->addWidget(itsMenuGui);

        connect(itsMenuGui, SIGNAL(SIG_PLAYGAME()), this, SLOT(onSelectPlayGame()));
        connect(itsMenuGui, SIGNAL(SIG_SETTING()), this, SLOT(onSelectSetting()));
        connect(itsMenuGui, SIGNAL(SIG_QUIT()), this, SLOT(onSelectQuit()));

        itsPauseGui->hide();
        delete itsPauseGui;
        itsPauseGui = nullptr;

        delete itsLevelBonusgui;
        itsLevelBonusgui = nullptr;
        //envoyer un signal pour stopper la mise a jour du modèle

        itsMenuGui->show();
        emit SIG_SoundsToBePlayed(2);
    }
    else
    {
        emit SIG_QUIT();
    }

    //qDebug()<<"fin de select quit";

}

void GUI::onCloseOptionMenu()
{
    //qDebug()<<"debut de select close option";

    itsOptionGui->hide();

    if(itsLevelGui == nullptr and itsLevelBonusgui == nullptr)//on est pas en jeu
    {
        itsMenuGui = new MenuGUI(this, SETTING);
        itsLayout->addWidget(itsMenuGui);


        itsMenuGui->show();

        connect(itsMenuGui, SIGNAL(SIG_PLAYGAME()), this, SLOT(onSelectPlayGame()));
        connect(itsMenuGui, SIGNAL(SIG_SETTING()), this, SLOT(onSelectSetting()));
        connect(itsMenuGui, SIGNAL(SIG_QUIT()), this, SLOT(onSelectQuit()));
    }
    else// on est en jeu
    {
        itsPauseGui = new PauseGui(this, SETTINGINGAME);
        itsLayout->addWidget(itsPauseGui);

        itsPauseGui->show();

        connect(this->itsPauseGui, SIGNAL(SIG_RESUME()), this, SLOT(onSelectResume()));
        connect(this->itsPauseGui, SIGNAL(SIG_SETTINGINGAME()), this, SLOT(onSelectSetting()));
        connect(this->itsPauseGui, SIGNAL(SIG_GOBACKTOMENU()), this, SLOT(onSelectQuit()));
    }

    delete itsOptionGui;
    itsOptionGui = nullptr;

    //qDebug()<<"fin de close option";

}

void GUI::onSelectResume()
{
    //qDebug()<<"debut de select resume";

    itsPauseGui->hide();
    delete itsPauseGui;
    itsPauseGui = nullptr;


    if(itsLevelGui != nullptr){
        itsLevelGui->show();
    }
    else if(itsLevelBonusgui != nullptr){
        itsLevelBonusgui->show();
    }

    //lancer un signal pour relancer le modèle
    itsGame->itsQTimer->start(8);
    //qDebug()<<"fin de select resume";

}

void GUI::onBonusDoor()
{
    if (itsLevelGui != nullptr)
    {
        itsLevelGui->hide();
        delete itsLevelGui;
        itsLevelGui = nullptr;
        itsGame->getItsLevel()->resetLevel();
        itsLevelBonusgui = new LevelBonusgui(this, itsGame);
        itsLayout->addWidget(itsLevelBonusgui);
        itsLevelBonusgui->show();
    }

}

void GUI::ExitBonusDoor()
{
    itsLevelBonusgui->hide();
    delete itsLevelBonusgui;
    itsLevelBonusgui = nullptr;
    itsGame->getItsLevel()->resetLevel();

    itsLevelGui = new LevelGui(this, itsGame);
    itsLayout->addWidget(itsLevelGui);
    for(Player* p: *itsGame->getItsLevel()->getItsPlayers())
    {
        p->setItsX(itsGame->getItsLevel()->getItsDoor()->getItsX());
        p->setItsY(itsGame->getItsLevel()->getItsDoor()->getItsY());
        p->getItsShape()->moveTo(itsGame->getItsLevel()->getItsDoor()->getItsX(), itsGame->getItsLevel()->getItsDoor()->getItsY());
        itsGame->getItsLevel()->getItsDoor()->setItsAlreadyOpen(true);
    }
    itsLevelGui->show();
}

void GUI::onClosedShop()
{
    itsShopGui->hide();
    itsLevelGui->show();
    itsGame->itsQTimer->start(8);

    delete itsShopGui;
    itsShopGui = nullptr;
}


void GUI::setItsGame(Game *newItsGame)
{
    itsGame = newItsGame;
}

void GUI::OpenShop()
{
    itsShopGui = new ShopGui(this);
    itsLayout->addWidget(itsShopGui);
    itsGame->itsQTimer->stop();

    itsLevelGui->hide();
    itsShopGui->show();

    connect(itsShopGui, SIGNAL(SIG_SHOPCLOSE()), this, SLOT(onClosedShop()));
}

