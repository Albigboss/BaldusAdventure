#include "player.h"
#include <QPixmap>
#include "controleur/obstacle.h"
#include <QDebug>








Player::Player(int aX, int aY, QRect *aShape) : Entities(aX, aY, aShape)
{
    itsFirstSpellcoolDown = new QTimer;
    itsSecondSpellcoolDown = new QTimer;


    std::list<QPixmap> *SpritePlayer = new std::list<QPixmap>;
    SpritePlayer->push_back(QPixmap(":/Player/images/Player/Perso_Stand.png"));
    SpritePlayer->push_back(QPixmap(":/Player/images/Player/Perso_StandL.png"));
    this->setItsPixMap(SpritePlayer);


    connect(itsFirstSpellcoolDown, SIGNAL(timeout()), this, SLOT(onFirstSpellTimerOff()));
    connect(itsSecondSpellcoolDown, SIGNAL(timeout()), this, SLOT(onSecondSpellTimerOff()));
}

Player::~Player()
{
    delete itsFirstSpell;
    delete itsSecondSpell;
    delete itsFirstSpellcoolDown;
    delete itsSecondSpellcoolDown;
}






void Player::updatePlayer(std::list<Obstacle *> someObstacle, std::list<Enemy*>* someEnemy)
{
    if (itsWallJump && itsYSpeed !=0)
    {
        if (itsDirection == 1)
        {
            if (itsXSpeed >2)
            {
                itsXSpeed -= 0.1;
            }
        }
        else
        {
            if (itsXSpeed <-2)
            {
                itsXSpeed += 0.1;
            }
        }
    }
    else
    {
        itsXSpeed = (itsRight - itsLeft)*itsXSpeedchange*3;
    }
    itsXSpeedchange = 1;
    if (itsYSpeed<maxgrave)
    {
        itsYSpeed += 0.2;
    }
    if (itsYSpeed > 2)
    {
        itsWallJump = false;
    }
    // Limit vertical speed to prevent excessive falling

    bool yColision = false;
    bool xColision = false;

    QRect fictivePlayerX = *getItsShape();
    fictivePlayerX.translate(itsXSpeed, 0);
    QRect fictivePlayerY = *getItsShape();
    fictivePlayerY.translate(0, itsYSpeed);


    int tempRemainingHearts = itsRemainingHearts;
    for (Obstacle* obstacle : someObstacle)
    {
        // Vérifier quel type de monstre c'est
        switch(obstacle->getItsType())
        {
        case WALL:
            if (fictivePlayerY.intersects(*obstacle->getItsShape()))
            {
                if (itsYSpeed > 0)
                {
                    // Si on descend, on arrête le mouvement vertical et on "fixe" le joueur
                    itsJump = true;
                    itsWallJump = false;
                    yColision = true;
                    itsYSpeed = 0;
                }
                else if (itsYSpeed < 0)
                {
                    // Si on monte, on arrête aussi
                    yColision = true;
                    itsYSpeed = 0;
                }

            }

            if (fictivePlayerX.intersects(*obstacle->getItsShape()))
            {
                // Activer la collision à droite et à gauche
                if (itsXSpeed > 0)
                {
                    xColision = true;
                }
                else if (itsXSpeed < 0)
                {
                    xColision = true;
                }
                break;
            }
        case TRAVERSABLE:
            if (fictivePlayerY.intersects(*obstacle->getItsShape()))
            {
                //le joueur n'a pas de collision tant qu'il n'est pas au dessus de la platform
                if (itsYSpeed > 0 and getItsShape()->bottom() <= obstacle->getItsShape()->top())
                {
                    // Si on descend, on arrête le mouvement vertical et on "fixe" le joueur
                    itsJump = true;
                    yColision = true;
                    itsYSpeed = 0;
                }
            }

            break;
        case TRAP:
            // Envoyer le signal de mort dès que le joueur touche les piques
            if (getItsShape()->intersects(*obstacle->getItsShape()))
            {
                emit SIG_playerDamage();
                return ;
            }
            break;
        }

        if(tempRemainingHearts != itsRemainingHearts)
        {
            break;
        }
    }

    ////qDebug()<<"la aussi";
    for (Enemy* enemy : *someEnemy)
    {
        // Envoyer le signal de mort dès que le joueur touche les Ennemi
        if (getItsShape()->intersects(*enemy->getItsShape()))
        {
            emit SIG_playerDamage();
            return ;//pas sur
        }
    }
    ////qDebug()<<"la aussi";

    if (itsYSpeed >1 || itsYSpeed<0)
    {
        itsJump = false;
    }

    // Si aucune collision verticale, appliquer la translation verticale
    if (!yColision)
    {
        getItsShape()->translate(0, itsYSpeed);
        setItsY(getItsY() + (int)itsYSpeed);
    }


    // Si aucune collision horizontale, appliquer la translation horizontale
    if (!xColision)
    {
        getItsShape()->translate(itsXSpeed, 0);
        setItsX(getItsX() + (int)itsXSpeed);
        if (itsXSpeed >0)
        {
            itsDirection=1;
        }
        else if (itsXSpeed <0)
        {
            itsDirection=-1;
        }
    }


    // Vérifier si le joueur est dans l'air et sur un mur
    if (xColision && itsYSpeed !=0 )
    {

        itsWallJump = false;
        canWallJump = true;
        maxgrave = 3;
    }
    else
    {
        canWallJump =false;
        maxgrave =10;
    }

    itsXSpeedchange = 1;
    itsYSpeedchange = 1;
}

void Player::jump()
{   // fait le saut si possible
    if (itsJump == true)
    {
        emit SIG_SoundsToBePlayed(1);
        itsYSpeed =-7 * itsYSpeedchange;
        itsWallJump = false;
    }
    // fait le saut sur le mur si possible
    else if (canWallJump == true)
    {
        emit SIG_SoundsToBePlayed(1);
        itsWallJump = true;
        itsYSpeed =-7 * itsYSpeedchange;
        if (itsDirection == 1)
        {
            itsXSpeed = -10;
        }
        else
        {
            itsXSpeed = 10;
        }
    }
}



void Player::loseHeart()
{
    if (itsRemainingHearts != 0)
    {
        itsRemainingHearts--;
    }
}


Spell *Player::getItsFirstSpell() const
{
    return itsFirstSpell;
}

void Player::setItsRight(bool newItsRight)
{
    itsRight = newItsRight;
}

void Player::setItsLeft(bool newItsLeft)
{
    itsLeft = newItsLeft;
}

Spell * Player::getItsSecondSpell() const
{
    return itsSecondSpell;
}

void Player::setItsSecondSpell(Spell *newItsSecondSpell)
{
    itsSecondSpell = newItsSecondSpell;
}



int Player::getItsRemainingHearts() const
{
    return itsRemainingHearts;
}

void Player::setItsRemainingHearts(int newItsRemainingHearts)
{
    itsRemainingHearts = newItsRemainingHearts;
}

int Player::getItsPiece() const
{
    return itsPiece;
}

void Player::setItsPiece(int newItsPiece)
{
    itsPiece = newItsPiece;
}

void Player::onFirstSpellTimerOff()
{
    //qDebug()<<"on first spell timer off";
    emit SIG_FirstSpellTimerOff();
    itsFirstSpellcoolDown->stop();
    //qDebug()<<"on first spell timer off";

}

void Player::onSecondSpellTimerOff()
{
    //qDebug()<<"on second spell timer off";
    emit SIG_SecondSpellTimerOff();
    itsSecondSpellcoolDown->stop();
    //qDebug()<<"on second spell timer off";

}

int Player::getItsXSpeed() const
{
    return itsXSpeed;
}


bool Player::getIsFirstSpell() const
{
    return isFirstSpell;
}

void Player::setIsFirstSpell(bool newIsFirstSpell)
{
    isFirstSpell = newIsFirstSpell;
}

void Player::setItsFirstSpell(Spell *newItsFirstSpell)
{
    itsFirstSpell = newItsFirstSpell;
}

bool Player::getItsRight() const
{
    return itsRight;
}

bool Player::getItsLeft() const
{
    return itsLeft;
}

int Player::getItsDirection() const
{
    return itsDirection;
}

void Player::setItsDirection(int newItsDirection)
{
    itsDirection = newItsDirection;
}

bool Player::getIsSecondSpell() const
{
    return isSecondSpell;
}

void Player::setIsSecondSpell(bool newIsSecondSpell)
{
    isSecondSpell = newIsSecondSpell;
}


QTimer *Player::getItsFirstSpellcoolDown() const
{
    return itsFirstSpellcoolDown;
}

QTimer *Player::getItsSecondSpellcoolDown() const
{
    return itsSecondSpellcoolDown;
}

void Player::setItsXSpeedchange(double newItsXSpeedchange)
{
    itsXSpeedchange = newItsXSpeedchange;
}

void Player::setItsYSpeedchange(double newItsYSpeedchange)
{
    itsYSpeedchange = newItsYSpeedchange;
}
