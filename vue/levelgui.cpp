#include "levelgui.h"


void LevelGui::setItsGameLose(bool newItsGameLose)
{
    itsGameLose = newItsGameLose;
}


bool LevelGui::getItsGameLose() const
{
    return itsGameLose;
}


void LevelGui::setItsResizeCoef()
{
    itsXRatio = double(width())/itsInitialWidth;
    itsYRatio = double(height())/itsInitialHeight;

}

void LevelGui::setItsQPixmap(QPixmap *newItsQPixmap)
{
    itsQPixmap = newItsQPixmap;
}

QPixmap *LevelGui::getItsQPixmap() const
{
    return itsQPixmap;
}

LevelGui::LevelGui(QWidget *parent, Game* aGame)
    : QWidget(parent), itsGame(aGame)
{


    if (itsGame->getItsLevel()->getItsPlayers()->size() != 0)
    {
        switch(itsGame->getItsLevel()->getItsLevelNumber())
        {
        case 1:
            itsGame->getItsLevel()->initLevelOne();
            break;
        case 2:
            //itsGame->getItsLevel().initLevelTwo();
            break;
        case 3:
            itsGame->getItsLevel()->initLevelThree();
            break;
        case 4:
            itsGame->getItsLevel()->initLevelFour();
            break;
        }

        itsQPixmap = itsGame->getItsLevel()->getItsBackground();
    }
    itsInitialHeight = 536;
    itsInitialWidth = 984;
}

LevelGui::~LevelGui() {}


void LevelGui::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter aPainter(this);


    int windowWidth = width();
    int windowHeight = height();
    int positionX;
    int positionY;

    Level* aLevel = itsGame->getItsLevel();
    Player *aPlayer = *aLevel->getItsPlayers()->begin();


    // Partie qui déplace la vue
    if (aLevel->getItsPlayers()->size() != 0)
    {
        positionX = aPlayer->getItsShape()->center().x()*itsXRatio;
        positionY = aPlayer->getItsShape()->center().y()*itsYRatio;

        itsDrawingArea = QRect(positionX/itsXRatio-windowWidth*1,positionY/itsYRatio-windowHeight, windowWidth*2, windowHeight*2);

        switch(aLevel->getItsLevelNumber())
        {
        case 1:
            if (positionX > (aLevel->getItsLevelWidth())*itsXRatio - windowWidth/2)
            {
                aPainter.translate((-aLevel->getItsLevelWidth())*itsXRatio + windowWidth, 0);
                //qDebug()<<1;
            } else if (positionX > windowWidth/2)
            {
                aPainter.translate(-positionX + windowWidth/2, 0);
                //qDebug()<<2;
            }
            else
            {
                //qDebug()<<3;
            }
            *itsQPixmap = itsQPixmap->scaledToHeight(windowHeight);
            break;
        case 3:
            if (positionY > (aLevel->getItsLevelHeight())*itsYRatio - windowHeight/2)
            {
                aPainter.translate(0, (-aLevel->getItsLevelHeight())*itsYRatio + windowHeight);
            } else if (positionY > windowHeight/2)
            {
                aPainter.translate(0, -positionY + windowHeight/2);
            }
            *itsQPixmap = itsQPixmap->scaledToWidth(windowWidth);
            break;

        case 4:
            if (positionY > (aLevel->getItsLevelHeight())*itsYRatio - windowHeight/2)
            {
                aPainter.translate(0, -(aLevel->getItsLevelHeight())*itsYRatio+ windowHeight);
            } else if (positionY > windowHeight/2)
            {
                aPainter.translate(0, -positionY + windowHeight/2);
            }
            *itsQPixmap = itsQPixmap->scaledToWidth(windowWidth);
            break;
        }
    }
    aPainter.drawPixmap(0,0,*itsQPixmap);

    if(aPlayer->getItsRemainingHearts() == 0 && itsGameLose == false){
        itsGameLose = true;
    }


    setItsResizeCoef();
    aPainter.scale(itsXRatio, itsYRatio);

    drawEnemy(&aPainter);
    drawObstacle(&aPainter);

    drawDoor(&aPainter);
    drawPlayer(&aPainter);
    drawSpell(&aPainter);
    drawHud(&aPainter);


}

void LevelGui::drawPlayer(QPainter *aPainter)
{
    aPainter->setPen(Qt::yellow);
    aPainter->setBrush(Qt::transparent);

    list<Player*>* aPlayerList = itsGame->getItsLevel()->getItsPlayers();

    for (Player *p : *aPlayerList) {
        list<QPixmap>* aPixmapList = p->getItsPixMap();
        //qDebug()<<*p->getItsShape();
        aPainter->drawRect(*p->getItsShape());
        if(p->getItsDirection() == 1)
        {

            aPainter->drawPixmap(*p->getItsShape(), aPixmapList->front());
            //aPainter->drawPixmap(QRect(p->getItsX(),p->getItsY(),36,24),mageR_png);
        }
        else if(p->getItsDirection() == -1)
        {
            aPainter->drawPixmap(*p->getItsShape(),aPixmapList->back());
        }
    }
}



void LevelGui::drawEnemy(QPainter *aPainter)
{
    aPainter->setPen(Qt::red);
    aPainter->setBrush(Qt::SolidPattern);
    itsGame->getItsLevel()->ennemyDead();

    list<Enemy*>* aEnemyList = itsGame->getItsLevel()->getItsEnemy();
    list<ShooterEnemy*>* aShooterEnemyList = itsGame->getItsLevel()->getItsShooterEnemy();





    for (Enemy* e : *aEnemyList)
    {
        if(itsDrawingArea.intersects(*e->getItsShape()))
        {
            if(e->getItsPixMap() != nullptr){
                const QPixmap temp1 = e->getItsPixMap()->back();
                const QPixmap temp2 = e->getItsPixMap()->front();
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

    }


    aPainter->setPen(Qt::yellow);
    for (ShooterEnemy* se : *aShooterEnemyList)
    {
        if(itsDrawingArea.intersects(*se->getItsShape()))
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
}

void LevelGui::drawObstacle(QPainter *aPainter)
{
    aPainter->setBrush(Qt::transparent);

    list<Obstacle*> *anObstacleList = itsGame->getItsLevel()->getItsObstacles();

    aPainter->setPen(Qt::cyan);

    if(itsGame->getItsLevel()->getItsShop() != nullptr){
        aPainter->drawRect(*itsGame->getItsLevel()->getItsShop()->getItsShape());
        aPainter->drawPixmap(*itsGame->getItsLevel()->getItsShop()->getItsShape(), itsGame->getItsLevel()->getItsShop()->getItsPixMap()->front());
    }

    for(Obstacle *o: *anObstacleList)
    {
        if(itsDrawingArea.intersects(*o->getItsShape()))
        {
            // Set the pen and brush color for the obstacle
            if(o->getItsType()==WALL)
                aPainter->setPen(Qt::white);
            else if(o->getItsType()==TRAP)
                aPainter->setPen(Qt::green);
            else
                aPainter->setPen(Qt::magenta);
            //aPainter->setBrush(Qt::SolidPattern);

            // Draw the obstacle rectangle
            //aPainter->drawRect(o->getItsX(), o->getItsY(), o->getItsShape()->width(), o->getItsShape()->height());
            aPainter->drawPixmap(o->getItsX(), o->getItsY(), o->getItsShape()->width(), o->getItsShape()->height(), o->getItsPixMap()->front());
        }
    }
}

void LevelGui::drawHud(QPainter *aPainter)
{
    //QPixmap Piece(":/hud/images/hud/Hud-piece.png");

    int positionX;
    int positionY;
    int levelWidth = itsGame->getItsLevel()->getItsLevelWidth();
    int levelHeight = itsGame->getItsLevel()->getItsLevelHeight();
    int windowWidth = width();
    int windowHeight = height();
    list<Player*> *Players = itsGame->getItsLevel()->getItsPlayers();


    if (Players->size() != 0)
    {


        positionX = Players->front()->getItsShape()->center().x()*itsXRatio;
        positionY = Players->front()->getItsShape()->center().y()*itsYRatio;
        QRect zoneTexte(windowWidth/32, windowHeight/18, windowWidth, windowHeight);
        int fontSize = qMin(zoneTexte.width()/32, zoneTexte.height()/18);
        QFont font = aPainter->font();
        font.setPointSize(fontSize);
        aPainter->setFont(font);
        aPainter->setPen(QColorConstants::Svg::brown);

        if(itsGame->getItsLevel()->getItsLevelNumber() == 1 or itsGame->getItsLevel()->getItsLevelNumber() == 2)
        {
            for (Player *p : *Players) {

                QString texte = QString::number(p->getItsPiece());

                unsigned int elapsedTime = itsGame->getItsElapsedTime();

                QString tempTime = QString::number(elapsedTime/60000)+QString(" : ");
                if((elapsedTime-60000*(elapsedTime/60000))/1000 < 10)
                {
                    tempTime += QString::number(0);
                }

                if(positionX > ((levelWidth)*itsXRatio - windowWidth/2))//end of the level, view is fixed
                {


                    //qDebug()<<"la";
                    if(p->getItsRemainingHearts() == 3){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-3.png");
                        aPainter->drawPixmap(levelWidth-975, 0,itsHudHeartThreePixmap->width()/3 * windowWidth/1024 , itsHudHeartThreePixmap->height()/3 *windowHeight/576, *itsHudHeartThreePixmap);
                    }
                    else if(p->getItsRemainingHearts() == 2){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-2.png");
                        aPainter->drawPixmap(levelWidth-975, 0,itsHudHeartTwoPixmap->width()/3 * windowWidth/1024 , itsHudHeartTwoPixmap->height()/3 *windowHeight/576, *itsHudHeartTwoPixmap);
                    }
                    else if(p->getItsRemainingHearts() == 1){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-1.png");
                        aPainter->drawPixmap(levelWidth-975, 0,itsHudHeartOnePixmap->width()/3 * windowWidth/1024 , itsHudHeartOnePixmap->height()/3 *windowHeight/576, *itsHudHeartOnePixmap);
                    }

                    //display of the number of pieces
                    aPainter->drawText(levelWidth-110*itsXRatio, windowHeight*0.08, texte);

                    //display of the piece logo
                    aPainter->drawPixmap(levelWidth-50*itsXRatio, windowHeight/40, itsPieceHudPixmap->width()*windowWidth*0.0001, itsPieceHudPixmap->height()*windowHeight*0.000175, *itsPieceHudPixmap);

                    //display the elapsed time
                    aPainter->drawText((levelWidth-473)-51*itsXRatio, -1+43*itsYRatio, tempTime+QString::number((elapsedTime-60000*(elapsedTime/60000))/1000));
                }
                else if (positionX > windowWidth/2)//during the level, veiw is moving
                {
                    //qDebug()<<"pas la";
                    // Obtenir la position du joueur (par exemple, en coordonnées du monde)
                    int playerPosX = positionX/itsXRatio;

                    // Calculer la position du HUD par rapport à la position du joueur
                    // Exemple : le HUD reste dans le coin supérieur gauche de la fenêtre du joueur
                    int hudPosX = playerPosX - 483;  // Décalage par rapport au joueur


                    // Calculer la taille de l'image à afficher (en fonction de la taille de la fenêtre)
                    int scaledWidth = itsHudHeartThreePixmap->width() / 3 * windowWidth / 1024;
                    int scaledHeight = itsHudHeartThreePixmap->height() / 3 * windowHeight / 576;

                    // Dessiner l'image des cœurs à la position calculée
                    if(p->getItsRemainingHearts() == 3){
                        aPainter->drawPixmap(hudPosX, 0, scaledWidth, scaledHeight, *itsHudHeartThreePixmap);
                    }
                    else if(p->getItsRemainingHearts() == 2){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-2.png");
                        aPainter->drawPixmap(hudPosX, 0, scaledWidth, scaledHeight, *itsHudHeartTwoPixmap);
                    }
                    else if(p->getItsRemainingHearts() == 1){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-1.png");
                        aPainter->drawPixmap(hudPosX, 0, scaledWidth, scaledHeight, *itsHudHeartOnePixmap);
                    }

                    //display of the number of pieces
                    aPainter->drawText(hudPosX+975-110*itsXRatio, windowHeight*0.08, texte);

                    //display of the piece logo
                    aPainter->drawPixmap(hudPosX+975-50*itsXRatio, windowHeight/40, itsPieceHudPixmap->width()*windowWidth*0.0001, itsPieceHudPixmap->height()*windowHeight*0.000175, *itsPieceHudPixmap);

                    //display the elapsed time
                    aPainter->drawText(hudPosX+501-50*itsXRatio, -1+43*itsYRatio, tempTime+QString::number((elapsedTime-60000*(elapsedTime/60000))/1000));
                }
                else //start of the level, view is fixed
                {
                    if(p->getItsRemainingHearts() == 3){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-3.png");
                        aPainter->drawPixmap(10-itsXRatio*1, 0,itsHudHeartThreePixmap->width()/3 * windowWidth/1024 , itsHudHeartThreePixmap->height()/3 *windowHeight/576, *itsHudHeartThreePixmap);
                    }
                    else if(p->getItsRemainingHearts() == 2){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-2.png");
                        aPainter->drawPixmap(10-itsXRatio*1, 0,itsHudHeartTwoPixmap->width()/3 * windowWidth/1024 , itsHudHeartTwoPixmap->height()/3 *windowHeight/576, *itsHudHeartTwoPixmap);
                    }
                    else if(p->getItsRemainingHearts() == 1){
                        //QPixmap Heart(":/hud/images/hud/hud-heart-1.png");
                        aPainter->drawPixmap(10-itsXRatio*1, 0,itsHudHeartOnePixmap->width()/3 * windowWidth/1024 , itsHudHeartOnePixmap->height()/3 *windowHeight/576, *itsHudHeartOnePixmap);
                    }

                    //display of the number of pieces
                    aPainter->drawText(984-110*itsXRatio, -1+43*itsYRatio, texte);

                    //display of the piece logo
                    aPainter->drawPixmap(985-51*itsXRatio,  windowHeight/40, itsPieceHudPixmap->width()*windowWidth*0.0001, itsPieceHudPixmap->height()*windowHeight*0.000175, *itsPieceHudPixmap);

                    //display the elapsed time
                    aPainter->drawText(510-50*itsXRatio, -1+43*itsYRatio, tempTime+QString::number((elapsedTime-60000*(elapsedTime/60000))/1000));
                }


                // QPen aPen(Qt::SolidPattern,windowWidth/2);
                // aPen.setColor(QColor::fromRgb(133,66,54));

                // aPainter->setPen(aPen);
                // aPainter->setFont(QFont("",29));

                int fontSize = qMin(windowWidth / 48, windowHeight / 27);
                fontSize = qMin(fontSize, 24);

                QFont font = aPainter->font();
                font.setPointSize(fontSize);

                aPainter->setFont(font);

                QString spell1 = "Spell 1 : ";
                QString spell2 = "Spell 2 : ";


                if(p->getItsFirstSpellcoolDown()->remainingTime() == -1)
                {
                    spell1 += QString("Ready");
                }
                else
                {
                    spell1 += QString::number(p->getItsFirstSpellcoolDown()->remainingTime()/1000.);
                }
                if(p->getItsSecondSpellcoolDown()->remainingTime() == -1)
                {
                    spell2 += QString("Ready");
                }
                else
                {
                    spell2 += QString::number(p->getItsSecondSpellcoolDown()->remainingTime()/1000.);
                }

                //qDebug()<<spell1;
                //qDebug()<<spell2;

                if(positionX > ((levelWidth)*itsXRatio - windowWidth/2))//fin du niveau, après le déplacement de la vue
                {

                    aPainter->drawText(levelWidth-208-1*itsXRatio, -1+70*itsYRatio, spell1);
                    aPainter->drawText(levelWidth-208-1*itsXRatio, -1+95*itsYRatio, spell2);
                }
                else if (positionX > windowWidth/2) {
                    aPainter->drawText((positionX/itsXRatio+284)-1*itsXRatio, -1+70*itsYRatio, spell1);
                    aPainter->drawText((positionX/itsXRatio+284)-1*itsXRatio, -1+95*itsYRatio, spell2);
                }
                else
                {
                    aPainter->drawText(850-75, -1+70*itsYRatio, spell1);
                    aPainter->drawText(850-75, -1+95*itsYRatio, spell2);
                }
            }
        }
        else if(itsGame->getItsLevel()->getItsLevelNumber() ==3 or itsGame->getItsLevel()->getItsLevelNumber() ==4) // Niveau vertical
        {
            for (Player *p : *Players) {
                QString texte = QString::number(p->getItsPiece());
                unsigned int elapsedTime = itsGame->getItsElapsedTime();

                QString tempTime = QString::number(elapsedTime / 60000) + " : ";
                if ((elapsedTime % 60000) / 1000 < 10)
                    tempTime += "0";
                tempTime += QString::number((elapsedTime % 60000) / 1000);

                // --- Responsive scaling ---
                int margin = windowWidth / 50; // s’adapte à la taille
                int scaledHeartWidth = itsHudHeartThreePixmap->width() / 3 * windowWidth / 1024;
                int scaledHeartHeight = itsHudHeartThreePixmap->height() / 3 * windowHeight / 576;

                int pieceIconWidth = itsPieceHudPixmap->width() * windowWidth * 0.0001;
                int pieceIconHeight = itsPieceHudPixmap->height() * windowHeight * 0.000175;

                // --- Setup texte ---
                int fontSize = qMin(windowWidth / 64, windowHeight / 36);
                fontSize = qMin(fontSize, 22);

                QFont font = aPainter->font();
                font.setPointSize(fontSize);
                aPainter->setFont(font);
                aPainter->setPen(QColorConstants::Svg::brown);

                // === HUD ===

                if(positionY < (levelHeight*itsYRatio)-windowHeight/2)
                {
                    // Coeurs (en haut à gauche)
                    if (p->getItsRemainingHearts() == 3)
                        aPainter->drawPixmap(margin, positionY/itsYRatio-250, scaledHeartWidth, scaledHeartHeight, *itsHudHeartThreePixmap);
                    else if (p->getItsRemainingHearts() == 2)
                        aPainter->drawPixmap(margin, positionY/itsYRatio-250, scaledHeartWidth, scaledHeartHeight, *itsHudHeartTwoPixmap);
                    else
                        aPainter->drawPixmap(margin, positionY/itsYRatio-250, scaledHeartWidth, scaledHeartHeight, *itsHudHeartOnePixmap);

                    // Chrono (haut centre)
                    aPainter->drawText(windowWidth / 2 +470- 500*itsXRatio, positionY/itsYRatio-250+25*itsYRatio, tempTime);

                    // Pièce (haut droite)
                    int pieceX = windowWidth - margin - pieceIconWidth;
                    //qDebug()<<pieceX+950-950*itsXRatio<<"  --  "<<margin;
                    aPainter->drawPixmap(pieceX+950-950*itsXRatio, positionY/itsYRatio-250, pieceIconWidth, pieceIconHeight, *itsPieceHudPixmap);

                    // Nombre de pièces (à gauche du logo pièce)
                    aPainter->drawText(pieceX + 950-1000*itsXRatio, positionY/itsYRatio-250 + pieceIconHeight * 0.8, texte);

                    // Sorts (en dessous du logo pièce)
                    QString spell1 = "Spell 1 : ";
                    QString spell2 = "Spell 2 : ";

                    if (p->getItsFirstSpellcoolDown()->remainingTime() == -1)
                        spell1 += "Ready";
                    else
                        spell1 += QString::number(p->getItsFirstSpellcoolDown()->remainingTime() / 1000.);

                    if (p->getItsSecondSpellcoolDown()->remainingTime() == -1)
                        spell2 += "Ready";
                    else
                        spell2 += QString::number(p->getItsSecondSpellcoolDown()->remainingTime() / 1000.);

                    aPainter->drawText(pieceX + 975-1050*itsXRatio, positionY/itsYRatio-160+10*itsYRatio, spell1);
                    aPainter->drawText(pieceX + 975-1050*itsXRatio, positionY/itsYRatio-130+10*itsYRatio, spell2);
                }
                else
                {
                    //qDebug()<<"la";
                    // Coeurs (en haut à gauche)
                    if (p->getItsRemainingHearts() == 3)
                    {
                        aPainter->drawPixmap(margin, 4014-2*itsYRatio, scaledHeartWidth, scaledHeartHeight, *itsHudHeartThreePixmap);
                    }
                    else if (p->getItsRemainingHearts() == 2)
                        aPainter->drawPixmap(margin, 4014-2*itsYRatio, scaledHeartWidth, scaledHeartHeight, *itsHudHeartTwoPixmap);
                    else
                        aPainter->drawPixmap(margin, 4014-2*itsYRatio, scaledHeartWidth, scaledHeartHeight, *itsHudHeartOnePixmap);

                    // Chrono (haut centre)
                    aPainter->drawText(windowWidth / 2 +470- 500*itsXRatio, 4014-2*itsYRatio+25*itsYRatio, tempTime);

                    // Pièce (haut droite)
                    int pieceX = windowWidth - margin - pieceIconWidth;
                    //qDebug()<<pieceX+950-950*itsXRatio<<"  --  "<<margin;
                    aPainter->drawPixmap(pieceX+950-950*itsXRatio, 4014-2*itsYRatio, pieceIconWidth, pieceIconHeight, *itsPieceHudPixmap);

                    // Nombre de pièces (à gauche du logo pièce)
                    aPainter->drawText(pieceX + 950-1000*itsXRatio, 4014-2*itsYRatio + pieceIconHeight * 0.8, texte);

                    // Sorts (en dessous du logo pièce)
                    QString spell1 = "Spell 1 : ";
                    QString spell2 = "Spell 2 : ";

                    if (p->getItsFirstSpellcoolDown()->remainingTime() == -1)
                        spell1 += "Ready";
                    else
                        spell1 += QString::number(p->getItsFirstSpellcoolDown()->remainingTime() / 1000.);

                    if (p->getItsSecondSpellcoolDown()->remainingTime() == -1)
                        spell2 += "Ready";
                    else
                        spell2 += QString::number(p->getItsSecondSpellcoolDown()->remainingTime() / 1000.);

                    aPainter->drawText(pieceX + 975-1050*itsXRatio, 4102+10*itsYRatio, spell1);
                    aPainter->drawText(pieceX + 975-1050*itsXRatio, 4132+10*itsYRatio, spell2);
                }
            }
        }
    }
}


void LevelGui::drawSpell(QPainter *aPainter)
{
    aPainter->setBrush(Qt::SolidPattern);

    list<Player*>* aPlayerList = itsGame->getItsLevel()->getItsPlayers();

    for (Player *p : *aPlayerList)
    {

        if(p->getIsFirstSpell()==true)
        {
            if(p->getItsFirstSpell()->getItsEntitie() != nullptr)
            {
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

void LevelGui::drawDoor(QPainter *aPainter)
{
    if (itsGame->getItsLevel()->getItsDoor() != nullptr)
    {
        aPainter->drawPixmap(*itsGame->getItsLevel()->getItsDoor()->getItsShape(),itsGame->getItsLevel()->getItsDoor()->getItsPixMap()->front());
    }
}





