#include "levelbonusgui.h"

bool LevelBonusgui::getItsGameLose() const
{
    return itsGameLose;
}

void LevelBonusgui::setItsGameLose(bool newItsGameLose)
{
    itsGameLose = newItsGameLose;
}

LevelBonusgui::LevelBonusgui(QWidget *parent, Game* aGame)
    : QWidget(parent), itsGame(aGame) {
    if (itsGame->getItsLevel()->getItsPlayers()->size() != 0)
    {
        itsGame->getItsLevel()->initLevelBonus();
    }

    itsInitialHeight = 536;
    itsInitialWidth = 984;


}

LevelBonusgui::~LevelBonusgui() {}

void LevelBonusgui::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter aPainter(this);



    Player *p = *itsGame->getItsLevel()->getItsPlayers()->begin();
    if(p->getItsRemainingHearts() == 0 && itsGameLose == false){
        itsGameLose = true;
    }

    int windowWidth = width();
    int windowHeight = height();
    itsXRatio = double(width())/itsInitialWidth;
    itsYRatio = double(height())/itsInitialHeight;


    drawHud(&aPainter);

    aPainter.scale(itsXRatio, itsYRatio);

    drawEnemy(&aPainter);

    drawObstacle(&aPainter);

    drawBonus(&aPainter);
    drawPlayer(&aPainter);
    drawSpell(&aPainter);

}



void LevelBonusgui::drawPlayer(QPainter *aPainter)
{
    aPainter->setPen(Qt::yellow);
    aPainter->setBrush(Qt::transparent);


    QPixmap mageR_png(":/Player/images/Player/Perso_Stand.png");
    QPixmap mageL_png(":/Player/images/Player/Perso_StandL.png");

    for (Player *p : *itsGame->getItsLevel()->getItsPlayers())
    {
        aPainter->drawRect(*p->getItsShape());
        if(p->getItsDirection() == 1)
        {
            aPainter->drawPixmap(*p->getItsShape(), mageR_png);
            //aPainter->drawPixmap(QRect(p->getItsX(),p->getItsY(),36,24),mageR_png);
        }
        else if(p->getItsDirection() == -1)
        {
            aPainter->drawPixmap(*p->getItsShape(), mageL_png);
        }
    }
}



void LevelBonusgui::drawEnemy(QPainter *aPainter)
{
    aPainter->setPen(Qt::red);
    aPainter->setBrush(Qt::SolidPattern);
    itsGame->getItsLevel()->ennemyDead();
    for (Enemy* e : *itsGame->getItsLevel()->getItsEnemy()){

        if(e->getItsPixMap() != nullptr){
            QPixmap temp1 = e->getItsPixMap()->back();
            QPixmap temp2 = e->getItsPixMap()->front();
            if(e->getItsDirection() == 1  &&  !temp1.isNull())
            {
                aPainter->drawPixmap(e->getItsX(),e->getItsY(),e->getItsShape()->width(),e->getItsShape()->height(),temp1);
            }
            else if(e->getItsDirection() == -1  &&  !temp2.isNull())
            {
                aPainter->drawPixmap(e->getItsX(),e->getItsY(),e->getItsShape()->width(),e->getItsShape()->height(),temp2);
            }
            else
            {
                aPainter->drawRect(*e->getItsShape());
            }
        }
        else
        {
            aPainter->drawRect(*e->getItsShape());
        }
    }

    aPainter->setPen(Qt::yellow);
    aPainter->setBrush(Qt::SolidPattern);
    for (ShooterEnemy* se : *itsGame->getItsLevel()->getItsShooterEnemy())
    {
        if(se->getItsPixMap() != nullptr){
            QPixmap temp1 = se->getItsPixMap()->back();
            QPixmap temp2 = se->getItsPixMap()->front();


            if(se->getItsDirection() == 1  &&  !temp1.isNull())
            {
                aPainter->drawPixmap(se->getItsX(),se->getItsY(),se->getItsShape()->width(),se->getItsShape()->height(),temp1);
            }
            else if(se->getItsDirection() == -1  &&  !temp2.isNull())
            {
                aPainter->drawPixmap(se->getItsX(),se->getItsY(),se->getItsShape()->width(),se->getItsShape()->height(),temp2);
            }
            else
            {
                aPainter->drawRect(*se->getItsShape());
            }


            QPixmap missile;
            if(se->getItsMissiles()->getItsDirection() == 1 && !se->getItsMissiles()->getItsPixMap()->front().isNull()){
                missile = se->getItsMissiles()->getItsPixMap()->front();
            }
            else if(se->getItsMissiles()->getItsDirection() == -1 && !se->getItsMissiles()->getItsPixMap()->back().isNull()){
                missile = se->getItsMissiles()->getItsPixMap()->back();
            }
            aPainter->drawPixmap(se->getItsMissiles()->getItsX(),
                                 se->getItsMissiles()->getItsY(),
                                 se->getItsMissiles()->getItsShape()->width(),
                                 se->getItsMissiles()->getItsShape()->height(),
                                 missile);

        }
        else
        {
            aPainter->drawRect(*se->getItsShape());
        }
    }
}

void LevelBonusgui::drawObstacle(QPainter *aPainter)
{
    aPainter->setBrush(Qt::transparent);
    for(Obstacle *o: *itsGame->getItsLevel()->getItsObstacles())
    {
        // Set the pen and brush color for the obstacle
        if(o->getItsType()==WALL)
        {
            aPainter->setPen(Qt::gray);
            aPainter->setBrush(QBrush(Qt::gray));
        }
        else if(o->getItsType()==TRAP)
            aPainter->setPen(Qt::green);
        else
        {
            aPainter->setPen(Qt::magenta);
            aPainter->setBrush(QBrush(QColorConstants::Svg::brown));
        }
        //aPainter->setBrush(Qt::SolidPattern);

        // Draw the obstacle rectangle
        aPainter->drawRect(o->getItsX(), o->getItsY(), o->getItsShape()->width(), o->getItsShape()->height());
    }
}

void LevelBonusgui::drawHud(QPainter *aPainter)
{
    int windowWidth = width();
    int windowHeight = height();
    QPixmap Piece(":/hud/images/hud/Hud-piece.png");


    int fontSize = qMin(windowWidth / 32, windowHeight / 18);
    QFont font = aPainter->font();
    font.setPointSize(fontSize);
    aPainter->setFont(font);
    aPainter->setPen(QColorConstants::Svg::brown);

    if (itsGame->getItsLevel()->getItsPlayers()->size() != 0)
    {

        aPainter->drawPixmap(windowWidth-windowWidth/16-windowWidth/64, windowHeight/40, windowWidth/16, windowHeight/9, Piece);
    }
    for (Player *p : *itsGame->getItsLevel()->getItsPlayers())
    {
        QString texte = QString::number(p->getItsPiece());
        aPainter->drawText(windowWidth*0.80, windowHeight/8, texte);

        if(p->getItsRemainingHearts() == 3){
            QPixmap Heart(":/hud/images/hud/hud-heart-3.png");
            aPainter->drawPixmap(windowWidth*0.01, 0,Heart.width()/3 * windowWidth/512 , Heart.height()/3 * windowHeight/288, Heart);
        }
        else if(p->getItsRemainingHearts() == 2){
            QPixmap Heart(":/hud/images/hud/hud-heart-2.png");
            aPainter->drawPixmap(windowWidth*0.01, 0,Heart.width()/3 * windowWidth/512 , Heart.height()/3 * windowHeight/288, Heart);
        }
        else if(p->getItsRemainingHearts() == 1){
            QPixmap Heart(":/hud/images/hud/hud-heart-1.png");
            aPainter->drawPixmap(windowWidth*0.01, 0,Heart.width()/3 * windowWidth/512 , Heart.height()/3 * windowHeight/288, Heart);
        }
    }
}


void LevelBonusgui::drawBonus(QPainter *aPainter)
{

    if (itsGame->getItsLevel()->getItsKey()->getItsTakeKey() == false)
    {
        aPainter->drawPixmap(*itsGame->getItsLevel()->getItsKey()->getItsShape(), itsGame->getItsLevel()->getItsKey()->getItsPixMap()->front());
        aPainter->drawPixmap(*itsGame->getItsLevel()->getItsChest()->getItsShape(), itsGame->getItsLevel()->getItsChest()->getItsPixMap()->front());
    }
    else
    {
        aPainter->drawPixmap(*itsGame->getItsLevel()->getItsChest()->getItsShape(), itsGame->getItsLevel()->getItsChest()->getItsPixMap()->front());
    }
    aPainter->drawPixmap(*itsGame->getItsLevel()->getItsDoorExit()->getItsShape(), itsGame->getItsLevel()->getItsDoorExit()->getItsPixMap()->front());
}


void LevelBonusgui::drawSpell(QPainter *aPainter)
{
    aPainter->setBrush(Qt::SolidPattern);
    for (Player *p : *itsGame->getItsLevel()->getItsPlayers())
    {

        if(p->getIsFirstSpell()==true)
        {
            if(p->getItsFirstSpell()->getItsEntitie() != nullptr){
                if(p->getItsFirstSpell()->getItsEntitie()->getItsPixMap() != nullptr)
                {
                    QPixmap temp1 = p->getItsFirstSpell()->getItsEntitie()->getItsPixMap()->front();
                    QPixmap temp2 = p->getItsFirstSpell()->getItsEntitie()->getItsPixMap()->back();


                    if(p->getItsFirstSpell()->getItsDirection() == -1  &&  !temp1.isNull())
                    {
                        aPainter->drawPixmap(p->getItsFirstSpell()->getItsEntitie()->getItsX(),p->getItsFirstSpell()->getItsEntitie()->getItsY(),p->getItsFirstSpell()->getItsEntitie()->getItsShape()->width(),p->getItsFirstSpell()->getItsEntitie()->getItsShape()->height(),temp1);
                    }

                    else if(p->getItsFirstSpell()->getItsDirection() == 1  &&  !temp2.isNull())
                    {
                        aPainter->drawPixmap(p->getItsFirstSpell()->getItsEntitie()->getItsX(),p->getItsFirstSpell()->getItsEntitie()->getItsY(),p->getItsFirstSpell()->getItsEntitie()->getItsShape()->width(),p->getItsFirstSpell()->getItsEntitie()->getItsShape()->height(),temp2);
                    }
                    else
                    {
                        aPainter->drawRect(*p->getItsFirstSpell()->getItsEntitie()->getItsShape());
                    }

                }
            }
        }

        if(p->getIsSecondSpell()==true)
        {
            if(p->getItsSecondSpell()->getItsEntitie() != nullptr)
            {
                if(p->getItsSecondSpell()->getItsEntitie()->getItsPixMap() != nullptr)
                {
                    QPixmap temp1 = p->getItsSecondSpell()->getItsEntitie()->getItsPixMap()->front();
                    QPixmap temp2 = p->getItsSecondSpell()->getItsEntitie()->getItsPixMap()->back();


                    if(p->getItsSecondSpell()->getItsDirection() == -1  &&  !temp1.isNull())
                    {
                        aPainter->drawPixmap(p->getItsSecondSpell()->getItsEntitie()->getItsX(),p->getItsSecondSpell()->getItsEntitie()->getItsY(),p->getItsSecondSpell()->getItsEntitie()->getItsShape()->width(),p->getItsSecondSpell()->getItsEntitie()->getItsShape()->height(),temp1);
                    }

                    else if(p->getItsSecondSpell()->getItsDirection() == 1  &&  !temp2.isNull())
                    {
                        aPainter->drawPixmap(p->getItsSecondSpell()->getItsEntitie()->getItsX(),p->getItsSecondSpell()->getItsEntitie()->getItsY(),p->getItsSecondSpell()->getItsEntitie()->getItsShape()->width(),p->getItsSecondSpell()->getItsEntitie()->getItsShape()->height(),temp2);
                    }
                    else
                    {
                        aPainter->drawRect(*p->getItsSecondSpell()->getItsEntitie()->getItsShape());
                    }
                }
            }
        }
    }
}

