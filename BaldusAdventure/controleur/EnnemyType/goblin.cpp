#include "goblin.h"
#include "QDebug"
#include "qpixmap.h"




Goblin::Goblin(int aLifePoints, int aReward, int aDirection, int aX, int aY, QRect *aShape, std::list<Player *> *aPlayer)
    :ShooterEnemy(aLifePoints, aReward, aDirection, aX, aY, aShape, aPlayer)
{
    std::list<QPixmap> *SpriteGoblin = new std::list<QPixmap>;
    SpriteGoblin->push_back(QPixmap(":/entites/images/entites/goblin-left-1.png"));
    SpriteGoblin->push_back(QPixmap(":/entites/images/entites/goblin-right-1.png"));
    this->setItsPixMap(SpriteGoblin);


    std::list<QPixmap> *SpriteMissile = new std::list<QPixmap>;
    SpriteMissile->push_back(QPixmap(":/entites/images/entites/arrow-left.png"));
    SpriteMissile->push_back(QPixmap(":/entites/images/entites/arrow-right.png"));
    ShooterEnemy::getItsMissiles()->setItsPixMap(SpriteMissile);
}

void Goblin::updateEnemyPosition(std::list<Obstacle *> someObstacles)
{
    isEnnemyColided = false;
    QRect CurrentGoblin = *getItsShape();
    QRect fictiveGoblinX = CurrentGoblin.translated(itsXSpeed * getItsDirection(), 0);
    QRect fictiveGoblinY = CurrentGoblin.translated(0, itsYSpeed);


    bool yCollision = false;
    bool xCollision = false;

    for (Obstacle* obstacle : someObstacles)
    {
        // Check if their is a collision between the player and X axes
        if (fictiveGoblinX.intersects(*obstacle->getItsShape()))
        {
            xCollision = true;
            setItsDirection(-getItsDirection());

        }

        // Check if their is a collision between the player and Y axes
        if (fictiveGoblinY.intersects(*obstacle->getItsShape()))
        {
            yCollision = true;

            //Check for the end of the platform, chage the direction.
            if(obstacle->getItsShape()->left() > fictiveGoblinX.left())
            {
                setItsDirection(-getItsDirection());
            }
            else if(obstacle->getItsShape()->right() < fictiveGoblinY.right())
            {
                setItsDirection(-getItsDirection());
            }
        }
    }

    for(Player * p: *getSomePlayer())
    {

        shoot(p);
        if (getItsShape()->intersects(*p->getItsShape()))
        {

            p->SIG_playerDamage();
            isEnnemyColided = true;
            return ;
        }
        else if (getItsMissiles()->getItsShape()->intersects(*p->getItsShape()))
        {
            p->SIG_playerDamage();
            isEnnemyColided = true;
            return ;
        }


        if (p->getItsFirstSpell()->getItsEntitie()!=nullptr)
        {
            if (getItsShape()->intersects(*p->getItsFirstSpell()->getItsEntitie()->getItsShape()))
            {
                takeDamage(p->getItsFirstSpell()->getItsDamage());
                p->getItsFirstSpell()->setItsEntitie(nullptr);
            }
        }
        if (p->getItsSecondSpell()->getItsEntitie()!=nullptr)
        {
            if (getItsShape()->intersects(*p->getItsSecondSpell()->getItsEntitie()->getItsShape()))
            {
                takeDamage(p->getItsSecondSpell()->getItsDamage());
                p->getItsSecondSpell()->setItsEntitie(nullptr);
            }
        }

    }
    // Move if their is no collision.
    if (!xCollision)
    {
        getItsShape()->translate(itsXSpeed * getItsDirection(), 0);
        setItsX(getItsX() + itsXSpeed * getItsDirection());
    }
    else
    {
        itsShoot = false;
    }
    if (!yCollision)
    {
        getItsShape()->translate(0, itsYSpeed);
        setItsY(getItsY() + itsYSpeed);
    }
    if (itsShoot == true)
    {
        getItsMissiles()->updateMissiles(someObstacles);
    }
    else
    {
        getItsMissiles()->setItsX(getItsX());
        getItsMissiles()->setItsY(getItsY());
        getItsMissiles()->getItsShape()->moveTo(getItsX(), getItsY());
    }
}

void Goblin::shoot(Player* itsPlayer)
{
    if (getItsY() == itsPlayer->getItsY() && itsShoot == false)
    {
        if(getItsDirection()==1 && itsPlayer->getItsX() >= getItsX() && itsPlayer->getItsX() <= getItsX()+500)
        {
            getItsMissiles()->setItsDirection(getItsDirection());
            itsShoot = true;
        }
        else if (getItsDirection()==-1 && itsPlayer->getItsX() <= getItsX() && itsPlayer->getItsX() >= getItsX()-500)
        {
            getItsMissiles()->setItsDirection(getItsDirection());
            itsShoot = true;
        }
    }
}
