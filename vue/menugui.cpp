#include "menugui.h"
#include <QPixmap>
#include <QFile>

MenuGUI::MenuGUI(QWidget *parent, MenuType aMenuType)
    : QWidget(parent), itsSelectedMenu(aMenuType)
{}

void MenuGUI::paintEvent(QPaintEvent *event)
{
    QPixmap image(":/menu/images/menus/menu.png");
    QPainter aPainter(this);

    if(!image.isNull())
    {
        aPainter.drawPixmap(0,0,width(), height(),image);
    }
    else
    {
        throw std::string("Failed to load the menu Picture");
    }

    aPainter.setBrush(Qt::NoBrush);
    aPainter.setPen(QPen(Qt::yellow,2));

    switch (itsSelectedMenu) {
    case 0:
        //aPainter.drawRect(width()/2-width()/8,height()/2-height()/7,width()/4, height()/7);
        aPainter.drawRect(width()*0.377,height()*0.32,width()*0.25, height()*0.15);
        break;
    case 1:
        aPainter.drawRect(width()*0.377,height()*0.485,width()*0.25, height()*0.15);
        break;
    case 2:
        aPainter.drawRect(width()*0.377,height()*0.652,width()*0.25, height()*0.15);
        break;
    default:
        break;
    }


    QPen aPen(Qt::SolidPattern,width()/2);
    aPen.setColor(QColor::fromRgb(133,66,54));

    aPainter.setPen(aPen);
    aPainter.setFont(QFont("",int(width()*0.02)));
    //qDebug()<<width()<<"  --  "<<width()*0.05;

    QFile aFile("./times.txt");
    if (!aFile.exists())
    {
        if (aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            aFile.close();  // on le ferme tout de suite
        }
    }
    else if(!aFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        qDebug()<<"error opening the file";
    }
    else
    {
        QTextStream aStream(&aFile);
        int i=1;

        aPainter.drawText(0.7 * width(), height() * (0.2 + i * 0.06), QString("Meilleurs Score"));
        while(!aStream.atEnd())
        {
            ++i;
            aPainter.drawText(0.7 * width(), height() * (0.2 + i * 0.06), QString::number(i-1)+QString(" : ")+aStream.readLine());

        }
    }
}


void MenuGUI::updateSelectedMenu(int aDirection)
{
    switch (itsSelectedMenu) {
    case PLAY:
        if(aDirection == 2)
        {
            itsSelectedMenu = SETTING;
        }
        else if(aDirection == 5)
        {
            emit SIG_PLAYGAME();
        }
        break;
    case SETTING:
        if(aDirection == 1)
        {
            itsSelectedMenu = PLAY;
        }
        else if(aDirection == 2)
        {
            itsSelectedMenu = QUIT;
        }
        else if(aDirection == 5)
        {
            emit SIG_SETTING();
        }
        break;
    case QUIT:
        if(aDirection == 1)
        {
            itsSelectedMenu = SETTING;
        }
        else if(aDirection == 5)
        {
            emit SIG_QUIT();
        }
        break;
    default:
        break;
    }
}

MenuGUI::~MenuGUI() {}
