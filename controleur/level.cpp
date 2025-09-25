#include "level.h"
#include "QtCore/qdebug.h"
#include "controleur/EnnemyType/bat.h"
#include "controleur/EnnemyType/ghost.h"
#include "controleur/EnnemyType/goblin.h"
#include "controleur/SpellType/SpellWaveV.h"
#include "controleur/SpellType/spellarrow.h"
#include "controleur/SpellType/spelljump.h"
#include "controleur/SpellType/spellmelee.h"
#include "controleur/SpellType/spellshield.h"
#include "controleur/SpellType/spellspeed.h"
#include "controleur/SpellType/spellwaveh.h"
#include "controleur/SpellType/spellwavevlarge.h"
#include "obstacle.h"






Shop *Level::getItsShop() const
{
    return itsShop;
}



Level::Level(int nbLevel, QObject *parent) : QObject{parent}, itsLevelNumber(nbLevel)
{
    itsPlayers = new list<Player*> ();
    Player *P1 = new Player(150, 460, new QRect(150, 460, 36, 28))    ;//Player *P1 = new Player(150, 467, new QRect(150, 467, 36, 28));
    itsPlayers->push_back(P1);
    itsEnemy = new list<Enemy*>;
    itsObstacles = new list<Obstacle*>;
    itsShooterEnemy = new list<ShooterEnemy*>;


    P1->setItsFirstSpell(new SpellWaveV(1, 1000, 12, 200, 1, 0, WEAK));
    P1->setItsSecondSpell(new spellWaveH(1, 1000, 12, 200, 1, 0, WEAK));

    //P1->setItsFirstSpell(new SpellWaveVLarge(1, 2000, 12, 200, 1, 0, WEAK));
    //P1->setItsSecondSpell(new SpellShield(0, 10000, 12, 200, 1, 0, WEAK));
    connect(P1, SIGNAL(SIG_playerDamage()), this, SLOT(onPlayerDamage()));
    connect(P1, SIGNAL(SIG_FirstSpellTimerOff()), this, SLOT(setCanThrowFirstSpell()));
    connect(P1, SIGNAL(SIG_SecondSpellTimerOff()), this, SLOT(setCanThrowSecondSpell()));


}

Level::~Level()
{
    delete itsObstacles;
    delete itsEnemy;
    delete itsShooterEnemy;
    delete itsPlayers;
    delete spell1;
    delete spell2;
}

void Level::initLevelOne()
{


    itsLevelNumber = 1;
    itsBackground = new QPixmap(":/levels/images/levels/level1.png");
    itsLevelWidth = 7060;



    //creation of obstacles
    Obstacle *wall1 = new Obstacle(1229,440,WALL,new QRect(1229,440,56,104),":/obstacles/images/entites/obstacles/obstacle-1.png");
    Obstacle *wall2 = new Obstacle(1800,400,WALL, new QRect(1800,400,60,36),":/obstacles/images/entites/obstacles/obstacles-2.png");
    Obstacle *wall3 = new Obstacle(1954,300,WALL, new QRect(1954,300,60,36), ":/obstacles/images/entites/obstacles/obstacles-2.png");
    Obstacle *wall5 = new Obstacle(2082,331,WALL, new QRect(2082,331,60,36),":/obstacles/images/entites/obstacles/obstacles-2.png");
    Obstacle *wall6 = new Obstacle(2112,208,WALL,new QRect(2112,208,56,352),":/obstacles/images/entites/obstacles/obstacles-3.png");
    Obstacle *wall7 = new Obstacle(2390,403,WALL, new QRect(2390,403,60,36),":/obstacles/images/entites/obstacles/obstacles-2.png");
    Obstacle *wall8 = new Obstacle(2542,339,WALL, new QRect(2542,339,194,70),":/obstacles/images/entites/obstacles/obstacles-4.png");
    Obstacle *wall9 = new Obstacle(3176,298,WALL, new QRect(3176,298,96,37),":/obstacles/images/entites/obstacles/obstacles-5.png");
    Obstacle *wall11 = new Obstacle(3406,207,WALL,new QRect(3406,207,56,352),":/obstacles/images/entites/obstacles/obstacles-3.png");
    Obstacle *wall12 = new Obstacle(3942,337,WALL,new QRect(3942,337,90,203),":/obstacles/images/entites/obstacles/obstacles-6.png");
    Obstacle *wall13 = new Obstacle(4226,331,WALL,new QRect(4226,331,60,36),":/obstacles/images/entites/obstacles/obstacles-2.png");
    Obstacle *wall14 = new Obstacle(4474,365,WALL,new QRect(4474,365,105,34),":/obstacles/images/entites/obstacles/obstacles-12.png");
    Obstacle *wall15 = new Obstacle(4770,347,WALL,new QRect(4770,347,46,180),":/obstacles/images/entites/obstacles/obstacles-8.png");
    Obstacle *wall16 = new Obstacle(4770,347,WALL,new QRect(4770,347,528,26),":/obstacles/images/entites/obstacles/obstacles-9.png");
    Obstacle *wall17 = new Obstacle(5324,439,WALL,new QRect(5324,439,56,104),":/obstacles/images/entites/obstacles/obstacle-1.png");
    Obstacle *wall18 = new Obstacle(5450,377,WALL,new QRect(5450,377,110,36),":/obstacles/images/entites/obstacles/obstacles-12.png");
    Obstacle *wall19 = new Obstacle(6042,391,WALL,new QRect(6042,391,528,26),":/obstacles/images/entites/obstacles/obstacles-9.png");

    Obstacle *wall20 = new Obstacle(0,495,WALL,new QRect(0,495,4030,40),":/menu/images/transparentPixmap.png");
    Obstacle *wall21 = new Obstacle(4414,495,WALL,new QRect(4414,495,1668,40),":/menu/images/transparentPixmap.png");
    Obstacle *wall22 = new Obstacle(6170,495,WALL,new QRect(6170,495,150,40),":/menu/images/transparentPixmap.png");
    Obstacle *wall23 = new Obstacle(6406,495,WALL,new QRect(6406,495,694,40),":/menu/images/transparentPixmap.png");

    Obstacle *wallLeft = new Obstacle(-4,0,WALL,new QRect(-4,0,4,500),":/menu/images/transparentPixmap.png");
    Obstacle *wallRight = new Obstacle(7062,0,WALL,new QRect(7062,0,4,500),":/menu/images/transparentPixmap.png");


    Obstacle *trav1 = new Obstacle(3838,360,TRAVERSABLE, new QRect(3838,360,104,12),":/obstacles/images/entites/obstacles/obstacles-7.png");
    //Obstacle *trav2 = new Obstacle(3912,347,TRAVERSABLE, new QRect(3912,347,30,32));
    Obstacle *trav3 = new Obstacle(6134,315,TRAVERSABLE, new QRect(6134,315,348,12),":/obstacles/images/entites/obstacles/obstacles-13.png");

    Obstacle *trap1 = new Obstacle(4029,495,TRAP,new QRect(4029,495,380,49),":/obstacles/images/entites/obstacles/obstacles-10.png");
    Obstacle *trap2 = new Obstacle(6086,495,TRAP,new QRect(6086,495,80,35),":/obstacles/images/entites/obstacles/obstacles-14.png");
    Obstacle *trap3 = new Obstacle(6326,495,TRAP,new QRect(6326,495,80,35),":/obstacles/images/entites/obstacles/obstacles-14.png");


    itsObstacles->push_back(wall20);
    itsObstacles->push_back(wall21);
    itsObstacles->push_back(wall22);
    itsObstacles->push_back(wall23);




    itsObstacles->push_back(wall1);
    itsObstacles->push_back(wall2);
    itsObstacles->push_back(wall3);
    itsObstacles->push_back(wall5);
    itsObstacles->push_back(wall6);
    itsObstacles->push_back(wall7);
    itsObstacles->push_back(wall8);
    itsObstacles->push_back(wall9);
    itsObstacles->push_back(wall11);
    itsObstacles->push_back(trav1);
    //itsObstacles->push_back(trav2);
    itsObstacles->push_back(wall12);
    itsObstacles->push_back(trap1);
    itsObstacles->push_back(wall13);
    itsObstacles->push_back(wall14);
    itsObstacles->push_back(wall15);
    itsObstacles->push_back(wall16);
    itsObstacles->push_back(wall17);
    itsObstacles->push_back(wall18);
    itsObstacles->push_back(wall19);
    itsObstacles->push_back(trap2);
    itsObstacles->push_back(trap3);
    itsObstacles->push_back(trav3);


    itsObstacles->push_back(wallLeft);
    itsObstacles->push_back(wallRight);

    //Ajout des ennemis dans le niveau :
    itsEnemy->push_back(new Skeleton(1,1,1,1300,450,new QRect(1300,450,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,1,2300,450,new QRect(2300,450,25,35)));
    itsShooterEnemy->push_back(new Goblin(1,1,1,2550,300,new QRect(2550,300,36,28), itsPlayers));
    itsShooterEnemy->push_back(new Goblin(1,1,1,3600,450,new QRect(3600,450,36,28), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,1,4500,330,new QRect(4500,330,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,1,4500,450,new QRect(4500,450,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,1,4900,450,new QRect(4900,450,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,1,5100,450,new QRect(5100,450,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,-1,5200,450,new QRect(5200,450,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,1,6150,330,new QRect(6150,330,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,-1,6450,330,new QRect(6450,330,25,35)));

}


void Level::initLevelThree()
{
    //qDebug()<<"dans le init level three";
    itsLevelNumber=3;
    for(Player *p : *itsPlayers)
    {
        p->setItsX(150);
        p->setItsY(4380);
        p->getItsShape()->moveTo(150,4380);
    }


    itsShop = new Shop(200, 4400,":/entites/images/entites/shop.png");


    itsBackground = new QPixmap(":/levels/images/levels/level3.png");
    if (!itsBackground)
    {
        //qDebug()<<"image non chargé";
    }
    itsLevelWidth = 1000;
    itsLevelHeight = 4530;
    itsDoor = new Door(460, 2150,":/entites/images/entites/door.png" ,new QRect(460, 2150, 40, 60));
    Obstacle *wall2 = new Obstacle(190,4300,WALL,new QRect(190,4300,200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall3 = new Obstacle(520,4200,WALL,new QRect(520,4200,200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall4 = new Obstacle(785,4100,WALL,new QRect(785,4100,200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall5 = new Obstacle(770,3300,WALL,new QRect(770,3300,30,600), ":/obstacles/images/entites/obstacles/obstacle-30-600-lvlVerticale.png");
    Obstacle *wall6 = new Obstacle(25,3270,WALL,new QRect(25,3270,775,30), ":/obstacles/images/entites/obstacles/obstacle-770-30-lvlVerticale.png" );
    Obstacle *wall7 = new Obstacle(30,3180,WALL,new QRect(30,3180, 150,30), ":/obstacles/images/entites/obstacles/obstacle-150-30-lvlVerticale.png");
    Obstacle *wall8 = new Obstacle(375,3125,WALL,new QRect(375,3125, 250,30), ":/obstacles/images/entites/obstacles/obstacle-250-30-lvlVerticale.png");
    Obstacle *wall9 = new Obstacle(30,3000,WALL,new QRect(30,3000, 200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall10 = new Obstacle(650,3050,WALL,new QRect(650,3050, 150,30), ":/obstacles/images/entites/obstacles/obstacle-150-30-lvlVerticale.png");
    Obstacle *wall11 = new Obstacle(315,2800,WALL,new QRect(315,2800, 300,30), ":/obstacles/images/entites/obstacles/obstacle-300-30-lvlVerticale.png");
    Obstacle *wall12 = new Obstacle(30,2700,WALL,new QRect(30, 2700, 170,30), ":/obstacles/images/entites/obstacles/obstacle-170-30-lvlVerticale.png");
    Obstacle *wall13 = new Obstacle(425,2700,WALL,new QRect(425,2700, 100,30), ":/obstacles/images/entites/obstacles/obstacle-100-30-lvlVerticale.png" );
    Obstacle *wall14 = new Obstacle(320,2210,WALL,new QRect(320,2210, 30,500), ":/obstacles/images/entites/obstacles/obstacle-30-500-lvlVerticale.png");
    Obstacle *wall15 = new Obstacle(601,2210,WALL,new QRect(601,2210, 30,500), ":/obstacles/images/entites/obstacles/obstacle-30-500-lvlVerticale.png");
    Obstacle *wall16 = new Obstacle(785,2700,WALL,new QRect(785,2700, 170,30), ":/obstacles/images/entites/obstacles/obstacle-170-30-lvlVerticale.png");
    Obstacle *wall17 = new Obstacle(626,2600,WALL,new QRect(626,2600, 205,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall18 = new Obstacle(755,2500,WALL,new QRect(755,2500, 200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall19 = new Obstacle(400,2500,WALL,new QRect(400,2500, 150,30), ":/obstacles/images/entites/obstacles/obstacle-150-30-lvlVerticale.png");
    Obstacle *wall20 = new Obstacle(425,2350,WALL,new QRect(425,2350, 181,30), ":/obstacles/images/entites/obstacles/obstacle-170-30-lvlVerticale.png");
    Obstacle *wall21 = new Obstacle(425,2210,WALL,new QRect(425,2210, 100,30), ":/obstacles/images/entites/obstacles/obstacle-100-30-lvlVerticale.png" );
    Obstacle *wall22 = new Obstacle(200,2520,WALL,new QRect(200,2520, 120,30), ":/obstacles/images/entites/obstacles/obstacle-120-30-lvlVerticale.png");
    Obstacle *wall23 = new Obstacle(200,2400,WALL,new QRect(200,2400, 120,30), ":/obstacles/images/entites/obstacles/obstacle-120-30-lvlVerticale.png");
    Obstacle *wall24 = new Obstacle(631,2300,WALL,new QRect(631,2300, 200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall25 = new Obstacle(90,2200,WALL,new QRect(90,2200, 75,30), ":/obstacles/images/entites/obstacles/obstacle-75-30-lvlVerticale.png");
    Obstacle *wall26 = new Obstacle(750, 2120, WALL, new QRect(750, 2120, 205, 30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");

    Obstacle *wall27 = new Obstacle(500, 2020, WALL, new QRect(500, 2020, 100, 30), ":/obstacles/images/entites/obstacles/obstacle-100-30-lvlVerticale.png" );
    Obstacle *wall28 = new Obstacle(320, 1750, WALL, new QRect(320, 1750, 30, 210), ":/obstacles/images/entites/obstacles/obstacle-30-210-lvlVerticale.png");
    Obstacle *wall29 = new Obstacle(480, 1750, WALL, new QRect(480, 1750, 100, 30), ":/obstacles/images/entites/obstacles/obstacle-100-30-lvlVerticale.png" );
    Obstacle *wall30 = new Obstacle(150, 1950, WALL, new QRect(150, 1950, 75, 30), ":/obstacles/images/entites/obstacles/obstacle-75-30-lvlVerticale.png");
    Obstacle *wall31 = new Obstacle(320, 1550, WALL, new QRect(320, 1550, 635, 30), ":/obstacles/images/entites/obstacles/obstacle-635-30-lvlVerticale.png" );
    Obstacle *wall32 = new Obstacle(410, 1500, WALL, new QRect(410, 1500, 30, 50), ":/obstacles/images/entites/obstacles/obstacle-30-50-lvlVerticale.png");


    Obstacle *trav1 = new Obstacle(30,4400,TRAVERSABLE, new QRect(30,4400,100,10), ":/obstacles/images/entites/obstacles/obstacles-100-10-trav-lvlVerticale.png");
    Obstacle *trav2 = new Obstacle(850,3970,TRAVERSABLE, new QRect(850,3970,105,10), ":/obstacles/images/entites/obstacles/obstacles-100-10-trav-lvlVerticale.png");
    Obstacle *trav3 = new Obstacle(230,3000,TRAVERSABLE, new QRect(230,3000,100,10), ":/obstacles/images/entites/obstacles/obstacles-100-10-trav-lvlVerticale.png");
    Obstacle *trav4 = new Obstacle(760,2920,TRAVERSABLE, new QRect(760,2920,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");
    Obstacle *trav5 = new Obstacle(140,2800,TRAVERSABLE, new QRect(140,2800,175,10), ":/obstacles/images/entites/obstacles/obstacles-175-10-trav-lvlVerticale.png");
    Obstacle *trav6 = new Obstacle(615,2800,TRAVERSABLE, new QRect(615,2800,175,10), ":/obstacles/images/entites/obstacles/obstacles-175-10-trav-lvlVerticale.png");
    Obstacle *trav7 = new Obstacle(526,2700,TRAVERSABLE, new QRect(526,2700,75,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav8 = new Obstacle(350,2700,TRAVERSABLE, new QRect(350,2700,75,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav9 = new Obstacle(831,2600,TRAVERSABLE, new QRect(831,2600,129,10), ":/obstacles/images/entites/obstacles/obstacles-124-10-trav-lvlVerticale.png");
    Obstacle *trav10 = new Obstacle(631,2500,TRAVERSABLE,new QRect(631,2500, 129,10), ":/obstacles/images/entites/obstacles/obstacles-124-10-trav-lvlVerticale.png");
    Obstacle *trav11 = new Obstacle(526,2600,TRAVERSABLE,new QRect(526,2600, 80,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav12 = new Obstacle(345,2600,TRAVERSABLE,new QRect(345,2600, 80,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav13 = new Obstacle(350,2350,TRAVERSABLE,new QRect(350,2350, 80,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav14 = new Obstacle(526,2210,TRAVERSABLE, new QRect(526,2210,75,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav15 = new Obstacle(350,2210,TRAVERSABLE, new QRect(350,2210,75,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav16 = new Obstacle(350,1950,TRAVERSABLE, new QRect(350,1950,100,10), ":/obstacles/images/entites/obstacles/obstacles-100-10-trav-lvlVerticale.png");
    Obstacle *trav17 = new Obstacle(140,1780,TRAVERSABLE, new QRect(140,1780,100,10), ":/obstacles/images/entites/obstacles/obstacles-100-10-trav-lvlVerticale.png");
    Obstacle *trav18 = new Obstacle(30,1550,TRAVERSABLE, new QRect(30,1550,290,10), ":/obstacles/images/entites/obstacles/obstacles-290-10-trav-lvlVerticale.png");
    Obstacle *trav19 = new Obstacle(30,1650,TRAVERSABLE, new QRect(30,1650,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");

    Obstacle *trap1 = new Obstacle(30,2400,TRAP,new QRect(30,2400,20,30), ":/obstacles/images/entites/obstacles/obstacles-20-30-left-trap-lvlVerticale.png");
    Obstacle *trap2 = new Obstacle(30,2250,TRAP,new QRect(30,2250,20,30), ":/obstacles/images/entites/obstacles/obstacles-20-30-left-trap-lvlVerticale.png");
    Obstacle *trap3 = new Obstacle(30,3030,TRAP,new QRect(30,3030,200,20), ":/obstacles/images/entites/obstacles/obstacles-200-20-trap-lvlVerticale.png");
    Obstacle *trap4 = new Obstacle(190,4330,TRAP,new QRect(190,4330,200,20), ":/obstacles/images/entites/obstacles/obstacles-200-20-trap-lvlVerticale.png");
    Obstacle *trap5 = new Obstacle(520,4230,TRAP,new QRect(520,4230,200,20), ":/obstacles/images/entites/obstacles/obstacles-200-20-trap-lvlVerticale.png");
    Obstacle *trap6 = new Obstacle(935,3210,TRAP,new QRect(935,3210,20,30), ":/obstacles/images/entites/obstacles/obstacles-20-30-right-trap-lvlVerticale.png");
    Obstacle *trap7 = new Obstacle(935,3100,TRAP,new QRect(935,3100,20,30), ":/obstacles/images/entites/obstacles/obstacles-20-30-right-trap-lvlVerticale.png");

    Obstacle *wall1 = new Obstacle(0,4500,WALL,new QRect(0,4500,985,30), ":/obstacles/images/entites/obstacles/obstacle-sol-lvlVerticale.png");
    Obstacle *wallLeft = new Obstacle(0,0,WALL,new QRect(0,0,30,4500), ":/obstacles/images/entites/obstacles/obstacle-wall-left.png");
    Obstacle *wallRight = new Obstacle(955,0,WALL,new QRect(955,0,30,4500), ":/obstacles/images/entites/obstacles/obstacle-wall-right.png");


    itsObstacles->push_back(wall2);
    itsObstacles->push_back(wall3);
    itsObstacles->push_back(wall4);
    itsObstacles->push_back(wall5);
    itsObstacles->push_back(wall6);
    itsObstacles->push_back(wall7);
    itsObstacles->push_back(wall8);
    itsObstacles->push_back(wall9);
    itsObstacles->push_back(wall10);
    itsObstacles->push_back(wall11);
    itsObstacles->push_back(wall12);
    itsObstacles->push_back(wall13);
    itsObstacles->push_back(wall14);
    itsObstacles->push_back(wall15);
    itsObstacles->push_back(wall16);
    itsObstacles->push_back(wall17);
    itsObstacles->push_back(wall18);
    itsObstacles->push_back(wall19);
    itsObstacles->push_back(wall20);
    itsObstacles->push_back(wall21);
    itsObstacles->push_back(wall22);
    itsObstacles->push_back(wall23);
    itsObstacles->push_back(wall24);
    itsObstacles->push_back(wall25);
    itsObstacles->push_back(wall26);
    itsObstacles->push_back(wall27);
    itsObstacles->push_back(wall28);
    itsObstacles->push_back(wall29);
    itsObstacles->push_back(wall30);
    itsObstacles->push_back(wall31);
    itsObstacles->push_back(wall32);


    itsObstacles->push_back(trav1);
    itsObstacles->push_back(trav2);
    itsObstacles->push_back(trav3);
    itsObstacles->push_back(trav4);
    itsObstacles->push_back(trav5);
    itsObstacles->push_back(trav6);
    itsObstacles->push_back(trav7);
    itsObstacles->push_back(trav8);
    itsObstacles->push_back(trav9);
    itsObstacles->push_back(trav10);
    itsObstacles->push_back(trav11);
    itsObstacles->push_back(trav12);
    itsObstacles->push_back(trav13);
    itsObstacles->push_back(trav14);
    itsObstacles->push_back(trav15);
    itsObstacles->push_back(trav16);
    itsObstacles->push_back(trav17);
    itsObstacles->push_back(trav18);
    itsObstacles->push_back(trav19);

    itsObstacles->push_back(trap1);
    itsObstacles->push_back(trap2);
    itsObstacles->push_back(trap3);
    itsObstacles->push_back(trap4);
    itsObstacles->push_back(trap5);
    itsObstacles->push_back(trap6);
    itsObstacles->push_back(trap7);



    itsObstacles->push_back(wall1);
    itsObstacles->push_back(wallLeft);
    itsObstacles->push_back(wallRight);

    itsEnemy->push_back(new Skeleton(1,1,1,850,4030,new QRect(850,4030,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,1,120,3210,new QRect(120,3210,25,35)));
    itsShooterEnemy->push_back(new Goblin(2,2,1,85,3210,new QRect(85,3210,36,28), itsPlayers));
    itsShooterEnemy->push_back(new Goblin(2,2,1,500,3060,new QRect(500,3060,36,28), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,1,180,3210,new QRect(180,3210,25,35)));
    itsEnemy->push_back(new Ghost(4,6,1,100,2900,new QRect(100,2900,44,40), itsPlayers));

    itsEnemy->push_back(new Bat(1,3,1,550,4000,new QRect(550,4000,76,20), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,1,380,2562,new QRect(380,2562,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,-1,550,2562,new QRect(550,2562,25,35)));

    itsEnemy->push_back(new Bat(1,3,1,450,2400,new QRect(450,2400,76,20), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,1,470,2462,new QRect(470,2462,25,35)));
    itsEnemy->push_back(new Skeleton(1,1,-1,430,2462,new QRect(430,2462,25,35)));

    itsShooterEnemy->push_back(new Goblin(2,2,1,500,2320,new QRect(500,2320,36,28), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,1,450,2312,new QRect(450,2312,25,35)));

    itsShooterEnemy->push_back(new Goblin(2,2,1,760,2462,new QRect(760,2462,36,28), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,-1,750,2562,new QRect(750,2562,25,35)));

    itsEnemy->push_back(new Bat(1,3,1,690,2272,new QRect(690,2272,76,20), itsPlayers));


}



void Level::initLevelFour()
{
    itsLevelNumber=4;
    for(Player *p : *itsPlayers)
    {
        p->setItsX(500);
        p->setItsY(4460);
        p->getItsShape()->moveTo(500,4460);
    }

    itsBackground = new QPixmap(":/levels/images/levels/level3.png");
    itsLevelWidth = 1000;
    itsLevelHeight = 4530;

    Obstacle *wallfloor = new Obstacle(0,4500,WALL,new QRect(0,4500,985,30), ":/obstacles/images/entites/obstacles/obstacle-sol-lvlVerticale.png");
    Obstacle *wallLeft = new Obstacle(0,0,WALL,new QRect(0,0,30,4500), ":/obstacles/images/entites/obstacles/obstacle-wall-left.png");
    Obstacle *wallRight = new Obstacle(955,0,WALL,new QRect(955,0,30,4500), ":/obstacles/images/entites/obstacles/obstacle-wall-right.png");
    itsObstacles->push_back(wallfloor);
    itsObstacles->push_back(wallLeft);
    itsObstacles->push_back(wallRight);

    Obstacle *trav1 = new Obstacle(457,4400,TRAVERSABLE,new QRect(457,4400,100,10), ":/obstacles/images/entites/obstacles/obstacles-100-10-trav-lvlVerticale.png");
    Obstacle *wall1 = new Obstacle(427,4100,WALL,new QRect(427,4100,30,315), ":/obstacles/images/entites/obstacles/obstacle-30-315-lvlVerticale.png");
    Obstacle *wall2 = new Obstacle(742,4325,WALL,new QRect(742,4325,213,30), ":/obstacles/images/entites/obstacles/obstacle-213-30-lvlVerticale.png");
    Obstacle *wall3 = new Obstacle(687,4125,WALL,new QRect(687,4125,100,30), ":/obstacles/images/entites/obstacles/obstacle-100-30-lvlVerticale.png");
    Obstacle *wall4 = new Obstacle(457,4100,WALL,new QRect(457,4100,100,30), ":/obstacles/images/entites/obstacles/obstacle-100-30-lvlVerticale.png");
    Obstacle *wall5 = new Obstacle(227,4300,WALL,new QRect(227,4300,200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall6 = new Obstacle(227,4145,WALL,new QRect(227,4145,200,30), ":/obstacles/images/entites/obstacles/obstacle-200-30-lvlVerticale.png");
    Obstacle *wall7 = new Obstacle(30,4050,TRAVERSABLE,new QRect(30,4050,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");
    Obstacle *wall8 = new Obstacle(230,4015,WALL,new QRect(230,4015,30,50), ":/obstacles/images/entites/obstacles/obstacle-30-50-lvlVerticale.png");
    Obstacle *wall9 = new Obstacle(230,4000,WALL,new QRect(230,4000,724,30), ":/obstacles/images/entites/obstacles/obstacle-724-30-lvlVerticale.png");
    Obstacle *wall10 = new Obstacle(30,3850,WALL,new QRect(30,3850,724,30), ":/obstacles/images/entites/obstacles/obstacle-724-30-lvlVerticale.png");
    Obstacle *wall11 = new Obstacle(230,3700,WALL,new QRect(230,3700,724,30), ":/obstacles/images/entites/obstacles/obstacle-724-30-lvlVerticale.png");
    Obstacle *wall12 = new Obstacle(477,3000,WALL,new QRect(477,3000,30,600), ":/obstacles/images/entites/obstacles/obstacle-30-600-lvlVerticale.png");
    Obstacle *wall13 = new Obstacle(171,3450,WALL,new QRect(171,3450,150,30), ":/obstacles/images/entites/obstacles/obstacle-150-30-lvlVerticale.png");
    Obstacle *wall14 = new Obstacle(30,3050,WALL,new QRect(30,3050,350,30), ":/obstacles/images/entites/obstacles/obstacle-350-30-lvlVerticale.png");

    Obstacle *trav2 = new Obstacle(30,3250,TRAVERSABLE,new QRect(30,3250,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");
    Obstacle *trav3 = new Obstacle(402,3200,TRAVERSABLE,new QRect(402,3200,75,10), ":/obstacles/images/entites/obstacles/obstacles-75-10-trav-lvlVerticale.png");
    Obstacle *trav4 = new Obstacle(30,2970,TRAVERSABLE,new QRect(30,2970,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");
    Obstacle *wall15 = new Obstacle(230,2970,WALL,new QRect(230,2970,524,30), ":/obstacles/images/entites/obstacles/obstacle-524-30-lvlVerticale.png");
    Obstacle *trav5 = new Obstacle(754,2970,TRAVERSABLE,new QRect(754,2970,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");
    Obstacle *wall16 = new Obstacle(707,3570,WALL,new QRect(707,3570,247,30), ":/obstacles/images/entites/obstacles/obstacle-250-30-lvlVerticale.png");
    Obstacle *wall17 = new Obstacle(657,3420,WALL,new QRect(657,3420,300,30), ":/obstacles/images/entites/obstacles/obstacle-300-30-lvlVerticale.png");
    Obstacle *wall18 = new Obstacle(506,3270,WALL,new QRect(506,3270,247,30), ":/obstacles/images/entites/obstacles/obstacle-250-30-lvlVerticale.png");
    Obstacle *wall19 = new Obstacle(707,3120,WALL,new QRect(707,3120,247,30), ":/obstacles/images/entites/obstacles/obstacle-250-30-lvlVerticale.png");

    Obstacle *trav6 = new Obstacle(392,2870,TRAVERSABLE,new QRect(392,2870,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");
    Obstacle *trav7 = new Obstacle(392,2770,TRAVERSABLE,new QRect(392,2770,200,10), ":/obstacles/images/entites/obstacles/obstacles-200-10-trav-lvlVerticale.png");

    Obstacle *wall20 = new Obstacle(30,2770,WALL,new QRect(30,2770,362,30), ":/obstacles/images/entites/obstacles/obstacle-362-30-lvlVerticale.png");
    Obstacle *wall21 = new Obstacle(592,2770,WALL,new QRect(592,2770,362,30), ":/obstacles/images/entites/obstacles/obstacle-362-30-lvlVerticale.png");

    itsObstacles->push_back(trav1);
    itsObstacles->push_back(wall1);
    itsObstacles->push_back(wall2);
    itsObstacles->push_back(wall3);
    itsObstacles->push_back(wall4);
    itsObstacles->push_back(wall5);
    itsObstacles->push_back(wall6);
    itsObstacles->push_back(wall7);
    itsObstacles->push_back(wall8);
    itsObstacles->push_back(wall9);
    itsObstacles->push_back(wall10);
    itsObstacles->push_back(wall11);
    itsObstacles->push_back(wall12);
    itsObstacles->push_back(wall13);
    itsObstacles->push_back(wall14);
    itsObstacles->push_back(trav2);
    itsObstacles->push_back(wall15);
    itsObstacles->push_back(trav3);
    itsObstacles->push_back(wall16);
    itsObstacles->push_back(wall17);
    itsObstacles->push_back(wall18);
    itsObstacles->push_back(wall19);
    itsObstacles->push_back(trav4);
    itsObstacles->push_back(trav5);
    itsObstacles->push_back(trav6);
    itsObstacles->push_back(wall20);
    itsObstacles->push_back(wall21);
    itsObstacles->push_back(trav7);





    Obstacle *trap1 = new Obstacle(30,4425,TRAP,new QRect(30,4425,20,75), ":/obstacles/images/entites/obstacles/obstacles-20-75-left-trap-lvlVerticale.png");
    itsObstacles->push_back(trap1);

    Obstacle *trap2 = new Obstacle(30,4300,TRAP,new QRect(30,4300,20,30), ":/obstacles/images/entites/obstacles/obstacles-20-30-left-trap-lvlVerticale.png");
    itsObstacles->push_back(trap2);

    Obstacle *trap3 = new Obstacle(934,4250,TRAP,new QRect(934,4250,20,75), ":/obstacles/images/entites/obstacles/obstacles-20-75-right-trap-lvlVerticale.png");
    itsObstacles->push_back(trap3);

    Obstacle *trap4 = new Obstacle(934,3925,TRAP,new QRect(934,3925,20,75), ":/obstacles/images/entites/obstacles/obstacles-20-75-right-trap-lvlVerticale.png");
    itsObstacles->push_back(trap4);

    Obstacle *trap5 = new Obstacle(30,3775,TRAP,new QRect(30,3775,20,75), ":/obstacles/images/entites/obstacles/obstacles-20-75-left-trap-lvlVerticale.png");
    itsObstacles->push_back(trap5);

    Obstacle *trap6 = new Obstacle(30,3375,TRAP,new QRect(30,3375,20,75), ":/obstacles/images/entites/obstacles/obstacles-20-75-left-trap-lvlVerticale.png");
    itsObstacles->push_back(trap6);

    Obstacle *trap7 = new Obstacle(457,3475,TRAP,new QRect(457,3475,20,75), ":/obstacles/images/entites/obstacles/obstacles-20-75-right-trap-lvlVerticale.png");
    itsObstacles->push_back(trap7);


    itsEnemy->push_back(new Skeleton(1, 1, 1, 770, 4290, new QRect(770, 4290, 25, 35)));

    itsShooterEnemy->push_back(new Goblin(2, 2, 1, 830, 3960, new QRect(830, 3960, 36, 28), itsPlayers));
    itsEnemy->push_back(new Skeleton(1, 1, 1, 730, 3960, new QRect(730, 3960, 25, 35)));
    itsEnemy->push_back(new Skeleton(1, 1, 1, 630, 3960, new QRect(630, 3960, 25, 35)));

    itsShooterEnemy->push_back(new Goblin(2,2,1,130,3810,new QRect(130,3810,36,28), itsPlayers));
    itsShooterEnemy->push_back(new Goblin(2,2,1,230,3810,new QRect(230,3810,36,28), itsPlayers));
    itsEnemy->push_back(new Skeleton(1,1,1,330,3810,new QRect(330,3810,25,35)));

    itsEnemy->push_back(new Bat(1,1,1,800,3540,new QRect(800,3540,76,20), itsPlayers));

    itsEnemy->push_back(new Skeleton(1,1,1,770,3530,new QRect(770,3530,25,35)));

    itsEnemy->push_back(new Skeleton(1,1,1,770,3380,new QRect(770,3380,25,35)));
    itsShooterEnemy->push_back(new Goblin(2,2,1,670,3380,new QRect(670,3380,36,28), itsPlayers));

    itsEnemy->push_back(new Skeleton(1,1,1,550,3230,new QRect(550,3230,25,35)));
    itsEnemy->push_back(new Ghost(1,1,1,810,3000,new QRect(810,3000,44,40), itsPlayers));
}


void Level::initLevelBonus()
{
    for(Player *p : *itsPlayers)
    {
        p->setItsX(45);
        p->setItsY(480);
        p->getItsShape()->moveTo(45,480);
    }
    itsLevelWidth = 1000;
    itsLevelHeight = 600;
    itsDoorExit = new Door(920, 455, ":/entites/images/entites/door.png" ,new QRect(920, 455, 40, 60));
    // Contoure
    Obstacle *wallFloor = new Obstacle(0,516,WALL,new QRect(0,516,1000,20));
    Obstacle *wallRoof = new Obstacle(0,0,WALL,new QRect(0,0,1000,20));
    Obstacle *wallRigth = new Obstacle(964,0,WALL,new QRect(964,0,20,600));
    Obstacle *wallLeft = new Obstacle(0,0,WALL,new QRect(0,0,20,600));
    itsObstacles->push_back(wallFloor);
    itsObstacles->push_back(wallRoof);
    itsObstacles->push_back(wallRigth);
    itsObstacles->push_back(wallLeft);
    if (itsDoorExit->getItsNumber() == 1)
    {
        itsKey = new Key(50, 40, ":/entites/images/entites/key.png", new QRect(50,40,18,36));
        itsChest = new Chest(50, 496, ":/entites/images/entites/chest.png", new QRect(50,496,40,20));

        // Platforme
        Obstacle *wall1 = new Obstacle(900,425,WALL,new QRect(900,425,40,20));
        Obstacle *wall2 = new Obstacle(700,400,WALL,new QRect(700,400,70,20));
        Obstacle *wall3 = new Obstacle(700,280,WALL,new QRect(700,280,20,80));
        Obstacle *wall4 = new Obstacle(400,320,WALL,new QRect(400,320,100,20));
        Obstacle *wall5 = new Obstacle(20,350,WALL,new QRect(20,350,180,20));
        Obstacle *wall6 = new Obstacle(20,100,WALL,new QRect(20,100,200,20));
        Obstacle *wall7 = new Obstacle(750,200,WALL,new QRect(750,200,100,20));
        Obstacle *wall8 = new Obstacle(280,20,WALL,new QRect(280,20,20,35));
        Obstacle *wall9 = new Obstacle(360,60,WALL,new QRect(360,60,20,120));
        Obstacle *wall10 = new Obstacle(380,60,WALL,new QRect(380,60,450,20));

        // itsObstacles->push_back();
        itsObstacles->push_back(wall1);
        itsObstacles->push_back(wall2);
        itsObstacles->push_back(wall3);
        itsObstacles->push_back(wall4);
        itsObstacles->push_back(wall5);
        itsObstacles->push_back(wall6);
        itsObstacles->push_back(wall7);
        itsObstacles->push_back(wall8);
        itsObstacles->push_back(wall9);
        itsObstacles->push_back(wall10);


        Obstacle *trav1 = new Obstacle(185,240,TRAVERSABLE,new QRect(185,240,20,10));
        Obstacle *trav2 = new Obstacle(440,210,TRAVERSABLE,new QRect(440,210,100,10));

        itsObstacles->push_back(trav1);
        itsObstacles->push_back(trav2);

    }
    else if (itsDoorExit->getItsNumber() == 2)
    {
        itsKey = new Key(900, 55, ":/entites/images/entites/key.png", new QRect(900,55,18,36));
        itsChest = new Chest(50, 496,  ":/entites/images/entites/chest.png",new QRect(50,496,40,20));

        Obstacle *wall1 = new Obstacle(120,400,WALL,new QRect(120,400,700,20));
        Obstacle *wall2 = new Obstacle(130,360,WALL,new QRect(130,360,20,40));
        Obstacle *wall3 = new Obstacle(800,360,WALL,new QRect(800,360,20,40));

        Obstacle *wall4 = new Obstacle(10,250,WALL,new QRect(10,250,710,20));
        Obstacle *wall5 = new Obstacle(700,210,WALL,new QRect(700,210,20,40));

        Obstacle *wall6 = new Obstacle(120,100,WALL,new QRect(120,100,800,20));
        Obstacle *wall7 = new Obstacle(130,60,WALL,new QRect(130,60,20,40));


        itsObstacles->push_back(wall1);
        itsObstacles->push_back(wall2);
        itsObstacles->push_back(wall3);
        itsObstacles->push_back(wall4);
        itsObstacles->push_back(wall5);
        itsObstacles->push_back(wall6);
        itsObstacles->push_back(wall7);

        Obstacle *trav1 = new Obstacle(20,410,TRAVERSABLE,new QRect(20,410,100,10));

        Obstacle *trav2 = new Obstacle(720,210,TRAVERSABLE,new QRect(720,210,200,10));

        Obstacle *trav3 = new Obstacle(20,110,TRAVERSABLE,new QRect(20,110,100,10));

        itsObstacles->push_back(trav1);
        itsObstacles->push_back(trav2);
        itsObstacles->push_back(trav3);

        itsEnemy->push_back(new Skeleton(1,1,1,150,365,new QRect(150,365,25,35)));
        itsEnemy->push_back(new Skeleton(1,1,1,200,365,new QRect(200,365,25,35)));
        itsEnemy->push_back(new Skeleton(1,1,1,400,365,new QRect(400,365,25,35)));
        itsEnemy->push_back(new Skeleton(1,1,1,150,190,new QRect(150,190,25,35)));
        itsShooterEnemy->push_back(new Goblin(1,1,1,400,190,new QRect(400,190,36,28), itsPlayers));
        itsShooterEnemy->push_back(new Goblin(1,1,1,250,190,new QRect(250,190,36,28), itsPlayers));
        itsEnemy->push_back(new Skeleton(1,1,1,400,55,new QRect(400,55,25,35)));
        itsShooterEnemy->push_back(new Goblin(1,1,1,250,55,new QRect(250,55,36,28), itsPlayers));
        itsEnemy->push_back((new Bat(1,1,1,700,55,new QRect(700,55,76,20),itsPlayers)));
    }
    else
    {
        itsKey = new Key(40, 55,":/entites/images/entites/key.png", new QRect(40,55,18,36));
        itsChest = new Chest(50, 496,  ":/entites/images/entites/chest.png", new QRect(50,496,40,20));

        Obstacle *wall1 = new Obstacle(120,350,WALL,new QRect(120,350,600,20));
        Obstacle *wall2 = new Obstacle(800,350,WALL,new QRect(800,350,200,20));
        Obstacle *wall4 = new Obstacle(400,330,WALL,new QRect(400,330,20,20));
        Obstacle *wall5 = new Obstacle(550,330,WALL,new QRect(550,330,20,20));

        Obstacle *wall6 = new Obstacle(20,250,WALL,new QRect(20,250,800,20));
        Obstacle *wall7 = new Obstacle(280,150,WALL,new QRect(280,150,20,100));
        // Obstacle *wall7 = new Obstacle(800,250,WALL,new QRect(800,250,200,20));
        // Obstacle *wall8 = new Obstacle(800,230,WALL,new QRect(800,230,20,20));
        // Obstacle *wall9 = new Obstacle(400,230,WALL,new QRect(400,230,20,20));
        // Obstacle *wall10 = new Obstacle(550,230,WALL,new QRect(550,230,20,20));



        itsObstacles->push_back(wall1);
        itsObstacles->push_back(wall2);
        itsObstacles->push_back(wall4);
        itsObstacles->push_back(wall5);
        itsObstacles->push_back(wall6);
        itsObstacles->push_back(wall7);
        // itsObstacles->push_back(wall8);
        // itsObstacles->push_back(wall9);
        // itsObstacles->push_back(wall10);
        // itsObstacles->push_back(wall11);

        Obstacle *trav1 = new Obstacle(20,350,TRAVERSABLE,new QRect(20,350,100,10));
        Obstacle *trav2 = new Obstacle(720,200,TRAVERSABLE,new QRect(720,200,100,10));
        Obstacle *trav3 = new Obstacle(400,170,TRAVERSABLE,new QRect(400,170,140,10));
        Obstacle *trav4 = new Obstacle(300,130,TRAVERSABLE,new QRect(300,130,25,10));
        Obstacle *trav5 = new Obstacle(20,100,TRAVERSABLE,new QRect(20,100,100,10));


        itsObstacles->push_back(trav1);
        itsObstacles->push_back(trav2);
        itsObstacles->push_back(trav3);
        itsObstacles->push_back(trav4);
        itsObstacles->push_back(trav5);

        itsEnemy->push_back(new Skeleton(1,1,1,450,310,new QRect(450,310,25,35)));
        itsEnemy->push_back(new Skeleton(1,1,1,850,310,new QRect(850,310,25,35)));

        Obstacle *trap1 = new Obstacle(200,340,TRAP,new QRect(200,340,25,10));
        Obstacle *trap2 = new Obstacle(920,340,TRAP,new QRect(920,340,25,10));
        Obstacle *trap3 = new Obstacle(270, 200,TRAP,new QRect(270,200,10,50));
        Obstacle *trap4 = new Obstacle(300, 240,TRAP,new QRect(300,240,400,10));

        itsObstacles->push_back(trap1);
        itsObstacles->push_back(trap2);
        itsObstacles->push_back(trap3);
        itsObstacles->push_back(trap4);
        // itsObstacles->push_back(trav5);

    }



}

void Level::resetLevel()
{
    //qDebug()<<"Debut de reset level size ennemi -> "<<itsEnemy->size();
    for(list<Enemy*>::iterator it = itsEnemy->begin(); it != itsEnemy->end(); ++it)
    {
        delete *it;
        *it = nullptr;

    }
    itsEnemy->clear();
    //qDebug()<<"Debut de reset level size ennemi -> "<<itsEnemy->size();


    //qDebug()<<" reset level size shooterEnnemi -> "<<itsShooterEnemy->size();
    for(list<ShooterEnemy*>::iterator it = itsShooterEnemy->begin(); it != itsShooterEnemy->end(); ++it)
    {
        delete *it;
        *it = nullptr;

    }
    itsShooterEnemy->clear();
    //qDebug()<<" reset level size shooterEnnemi -> "<<itsShooterEnemy->size();


    //qDebug()<<" reset level obstacles -> "<<itsObstacles->size();
    for(list<Obstacle*>::iterator it = itsObstacles->begin(); it != itsObstacles->end(); ++it)
    {
        delete *it;
        *it = nullptr;

    }
    itsObstacles->clear();
    //qDebug()<<" reset level obstacles -> "<<itsObstacles->size();


    //qDebug()<<" reset level door -> "<<itsDoor;
    delete itsDoor;
    itsDoor = nullptr;
    //qDebug()<<" reset level door -> "<<itsDoor;

    //qDebug()<<" reset level key -> "<<itsKey;
    delete itsKey;
    itsKey = nullptr;
    //qDebug()<<" reset level key -> "<<itsKey;

    //qDebug()<<" reset level chest -> "<<itsChest;
    delete itsChest;
    itsChest = nullptr;
    //qDebug()<<" reset level chest -> "<<itsChest;

    //qDebug()<<" reset level doorexit -> "<<itsDoorExit;
    delete itsDoorExit;
    itsDoorExit = nullptr;
    //qDebug()<<" reset level doorexit -> "<<itsDoorExit;
}



void Level::ennemyDead()
{
    for (auto it = itsEnemy->begin(); it != itsEnemy->end(); )
    {
        Enemy* e = *it; // Pointeur vers l'ennemi
        if (e->getItsLifePoints() <= 0) {
            // Suppression de l'ennemi de la liste
            itsPlayers->front()->setItsPiece(itsPlayers->front()->getItsPiece()+e->getItsReward());
            it = itsEnemy->erase(it); // erase() renvoie l'itérateur suivant

            // Libération de la mémoire
            delete e;
        }
        else {
            // Si l'ennemi est toujours en vie, on avance l'itérateur
            ++it;
        }
    }
    for (auto it = itsShooterEnemy->begin(); it != itsShooterEnemy->end(); )
    {
        ShooterEnemy* se = *it; // Pointeur vers l'ennemi
        if (se->getItsLifePoints() <= 0) {
            // Suppression de l'ennemi de la liste
            itsPlayers->front()->setItsPiece(itsPlayers->front()->getItsPiece()+se->getItsReward());
            it = itsShooterEnemy->erase(it); // erase() renvoie l'itérateur suivant

            // Libération de la mémoire
            delete se;
        }
        else {
            // Si l'ennemi est toujours en vie, on avance l'itérateur
            ++it;
        }
    }
}

void Level::onPlayerDamage()
{


    if (itsDoorExit == nullptr)
    {
        resetLevel();

        switch (itsLevelNumber) {
        case 1:
            initLevelOne();
            for (Player* p: *itsPlayers)
            {
            if(dynamic_cast<SpellShield*>(p->getItsFirstSpell()) && p->getItsFirstSpellcoolDown()->remainingTime() >= 5000){}
            else if(dynamic_cast<SpellShield*>(p->getItsSecondSpell()) && p->getItsSecondSpellcoolDown()->remainingTime() >= 5000){}
            else{
                p->loseHeart();
            }
            p->getItsShape()->moveTo(150, 460);
            p->setItsX(150);
            p->setItsY(460);


        }
        break;

        case 3:
            initLevelThree();
            
            for(Player* p: *itsPlayers)
            {
            if(dynamic_cast<SpellShield*>(p->getItsFirstSpell()) && p->getItsFirstSpellcoolDown()->remainingTime() >= 5000){}
            else if(dynamic_cast<SpellShield*>(p->getItsSecondSpell()) && p->getItsSecondSpellcoolDown()->remainingTime() >= 5000){}
            else{
                p->loseHeart();
            }
            p->setItsX(50);
            p->setItsY(4460);
            p->getItsShape()->moveTo(50, 4460);
            }
            break;
        case 4:
            initLevelFour();
            
            for(Player* p: *itsPlayers)
            {
            if(dynamic_cast<SpellShield*>(p->getItsFirstSpell()) && p->getItsFirstSpellcoolDown()->remainingTime() >= 5000){}
            else if(dynamic_cast<SpellShield*>(p->getItsSecondSpell()) && p->getItsSecondSpellcoolDown()->remainingTime() >= 5000){}
            else{
                p->loseHeart();
            }
            p->setItsX(500);
            p->setItsY(4460);
            p->getItsShape()->moveTo(500, 4460);
            }
            break;
        default:
            break;
        }
    }
    else
    {

        for(Player *p : *itsPlayers)
        {
            p->setItsX(45);
            p->setItsY(480);
            p->getItsShape()->moveTo(45,480);
            if(dynamic_cast<SpellShield*>(p->getItsFirstSpell()) && p->getItsFirstSpellcoolDown()->remainingTime() >= 5000){}
            else if(dynamic_cast<SpellShield*>(p->getItsSecondSpell()) && p->getItsSecondSpellcoolDown()->remainingTime() >= 5000){}
            else{
            p->loseHeart();
            }
        }
        resetLevel();
        initLevelBonus();
    }


    //qDebug()<<"ici";

    itsPlayers->front()->itsFirstSpellcoolDown->stop();
    itsPlayers->front()->itsSecondSpellcoolDown->stop();

    //qDebug()<<"c'étais là";

    canThrowFirstSpell = true;
    canThrowSecondSpell = true;

    //qDebug()<<"fin de player damage";


}



list<Enemy *>* Level::getItsEnemy() const
{
    return itsEnemy;

}

list<Obstacle *>* Level::getItsObstacles() const
{
    return itsObstacles;
}

list<Player *> *Level::getItsPlayers() const
{
    return itsPlayers;
}


QPixmap* Level::getItsBackground() const
{
    return itsBackground;
}

int Level::getItsLevelWidth() const
{
    return itsLevelWidth;
}

bool Level::getCanThrowFirstSpell() const
{
    return canThrowFirstSpell;
}


void Level::setCanThrowFirstSpell(bool newCanThrowFirstSpell)
{
    //qDebug()<<"debut de setcanthrowfirstspell";

    canThrowFirstSpell = newCanThrowFirstSpell;
    //qDebug()<<"fin de setcanthrowfirstspell";

}

bool Level::getCanThrowSecondSpell() const
{
    return canThrowSecondSpell;
}

void Level::setCanThrowSecondSpell(bool newCanThrowSecondSpell)
{
    //qDebug()<<"debut de setcanthrowsecondspell";

    canThrowSecondSpell = newCanThrowSecondSpell;
    //qDebug()<<"fin de setcanthrowsecondspell";

}



list<ShooterEnemy *> *Level::getItsShooterEnemy() const
{
    return itsShooterEnemy;
}

int Level::getItsLevelHeight() const
{
    return itsLevelHeight;
}

int Level::getItsLevelNumber() const
{
    return itsLevelNumber;
}

Door *Level::getItsDoor() const
{
    return itsDoor;
}

Key *Level::getItsKey() const
{
    return itsKey;
}

Chest *Level::getItsChest() const
{
    return itsChest;
}

Door *Level::getItsDoorExit() const
{
    return itsDoorExit;
}
