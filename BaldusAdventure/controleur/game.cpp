
#include "game.h"
#include "level.h"
#include <QDebug>

#include <QFile>


Game::Game():itsLevel(new Level(1))
{
    itsQTimer = new QTimer(this);
    connect(itsQTimer, SIGNAL(timeout()), this, SLOT(updateModel()));
    itsQTimer->start(8);
    //qDebug()<<"Thread Game : "<<itsQTimer->thread();
}

Game::~Game()
{
    delete itsLevel;
    delete itsQTimer;
}

void Game::updateModel()
{
    //qDebug()<<"debut de updateModel";
    for(Player* p: *itsLevel->getItsPlayers())
    {
        int tempRemainingHearts = p->getItsRemainingHearts();

        //qDebug()<<p;
        p->updatePlayer(*itsLevel->getItsObstacles(), itsLevel->getItsEnemy());
        //qDebug()<<"fin de update player "<<p;

        if(p->getItsRemainingHearts() != tempRemainingHearts)
        {
            //qDebug()<<"le nombre de coeurs à chnagé - fin de update model";
            return ;
        }
        //qDebug()<<"ici";
        if(p->getItsFirstSpell() && p->getItsFirstSpell()->getIsProjectileSpell() == true)
        {
            p->getItsFirstSpell()->updateSpell(itsLevel->getItsObstacles(), itsLevel->getItsEnemy(), itsLevel->getItsPlayers());
            if(p->getItsFirstSpell()->getItsEntitie() != nullptr)
            {
                if((p->getItsFirstSpell()->getItsEntitie()->getItsX() < p->getItsFirstSpell()->getItsMaxDistance() - (2*p->getItsFirstSpell()->getItsRange()) || p->getItsFirstSpell()->getItsEntitie()->getItsX() > p->getItsFirstSpell()->getItsMaxDistance()))                {
                    p->setIsFirstSpell(false);
                    p->getItsFirstSpell()->setItsEntitie(nullptr);
                }
            }
        }
        else if(p->getItsFirstSpell()->getIsProjectileSpell() == false && p->getIsFirstSpell())
        {
            p->getItsFirstSpell()->updateSpell(itsLevel->getItsObstacles(), itsLevel->getItsEnemy(), itsLevel->getItsPlayers());
            if(p->getItsFirstSpellcoolDown()->remainingTime() <= 5000){
                p->setIsFirstSpell(false);
            }
        }


        if(p->getItsSecondSpell() && p->getItsSecondSpell()->getIsProjectileSpell() == true)
        {
            p->getItsSecondSpell()->updateSpell(itsLevel->getItsObstacles(), itsLevel->getItsEnemy(), itsLevel->getItsPlayers());
            if(p->getItsSecondSpell()->getItsEntitie() != nullptr)
            {
                if((p->getItsSecondSpell()->getItsEntitie()->getItsX() < p->getItsSecondSpell()->getItsMaxDistance() - (2*p->getItsSecondSpell()->getItsRange()) || p->getItsSecondSpell()->getItsEntitie()->getItsX() > p->getItsSecondSpell()->getItsMaxDistance()))                {
                    p->setIsSecondSpell(false);
                    p->getItsSecondSpell()->setItsEntitie(nullptr);
                }
            }
        }
        else if(p->getItsSecondSpell()->getIsProjectileSpell() == false && p->getIsSecondSpell())
        {
            p->getItsSecondSpell()->updateSpell(itsLevel->getItsObstacles(), itsLevel->getItsEnemy(), itsLevel->getItsPlayers());
            if(p->getItsSecondSpellcoolDown()->remainingTime() <= 5000){
                p->setIsSecondSpell(false);
            }
        }

        if (itsLevel->getItsKey() != nullptr)
        {
            itsLevel->getItsKey()->KeyTake(p);
        }
        if (itsLevel->getItsChest() != nullptr)
        {
            if (itsLevel->getItsKey()->getItsTakeKey() == true)
            {
                itsLevel->getItsChest()->ChestTake(p);
            }
        }
    }
    //qDebug()<<"la";
    for(Enemy *e: *this->itsLevel->getItsEnemy())
    {
        e->updateEnemyPosition(*itsLevel->getItsObstacles());
    }


    for (ShooterEnemy *se : *this->itsLevel->getItsShooterEnemy())
    {
        se->updateEnemyPosition(*itsLevel->getItsObstacles());
        if(se->getisEnnemyColided())
        {
            break;

        }
    }

    itsElapsedTime += 8;
    //qDebug()<<"fin de updateModel";

}

Level * Game::getItsLevel() const
{
    return itsLevel;
}

void Game::setItsLevel(Level *newItsLevel)
{
    itsLevel = newItsLevel;
}

unsigned int Game::getItsElapsedTime() const
{
    return itsElapsedTime;
}



unsigned int Game::getItsScore()
{

    Player* tempPlayer = itsLevel->getItsPlayers()->front();

    itsScore = (1/(itsElapsedTime/10000.))*((tempPlayer->getItsPiece()+3)/3)*(itsLevel->getItsLevelNumber())*(2*tempPlayer->getItsRemainingHearts()+1)*1000 ;


    writeFile();
    return static_cast<unsigned int>(itsScore);
}

void Game::writeFile()
{
    QFile aFile("./times.txt");
    list<int>* aStringList = new list<int>;


    if (!aFile.exists())
    {
        if (aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            aFile.close();  // on le ferme tout de suite
        }
    }

    if(!aFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        //qDebug()<<"error opening the file";
    }
    else
    {
        QTextStream aStream(&aFile);

        while(!aStream.atEnd())
        {
            aStringList->push_back(aStream.readLine().toInt());
        }

        aFile.close();

        aStringList->push_back(itsScore);
        aStringList->sort();

        int i= aStringList->size();

        //qDebug()<<" ---Les Scores -----"<<i;

        if(!aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            //qDebug()<<"error opening the file";
        }
        else
        {
            for(int j = 0; j < i and j < 10; ++j)
            {
                //qDebug()<< aStringList->back();
                aStream << aStringList->back()<<"\n";

                aStringList->pop_back();

            }
            aFile.close();
        }


    }

    delete aStringList;
}
