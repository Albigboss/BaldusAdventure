#include <QPainter>

#include "pausegui.h"


PauseGui::PauseGui(QWidget *parent, PauseType aPauseType):QWidget(parent)
{
    itsSelectedPauseType = aPauseType;
}

void PauseGui::paintEvent(QPaintEvent *event)
{
    QPixmap image(":/menu/images/menus/pause.png");
    QPainter aPainter(this);

    aPainter.setPen(QColor(128,128,128,128));
    aPainter.drawRect(0,0,width(),height());

    if(!image.isNull())
    {
        aPainter.drawPixmap(0,0,width(), height(),image);
    }
    else
    {
        //throw std::string("Failed to load the pause Picture");
    }

    aPainter.setBrush(Qt::NoBrush);
    aPainter.setPen(QPen(Qt::yellow,2));

    switch (itsSelectedPauseType) {
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
}

void PauseGui::updateSelectedMenu(int aDirection)
{
    //1 = up, 2 = down, 5 = select
    switch (itsSelectedPauseType) {
    case RESUME:
        if(aDirection == 2)
        {
            itsSelectedPauseType = SETTINGINGAME;
        }
        else if(aDirection == 5)
        {
            emit SIG_RESUME();
        }
        break;
    case SETTINGINGAME:
        if(aDirection == 1)
        {
            itsSelectedPauseType = RESUME;
        }
        else if(aDirection == 2)
        {
            itsSelectedPauseType = GOBACKTOMENU;
        }
        else if(aDirection == 5)
        {
            emit SIG_SETTINGINGAME();
        }
        break;
    case GOBACKTOMENU:
        if(aDirection == 1)
        {
            itsSelectedPauseType = SETTINGINGAME;
        }
        else if(aDirection == 5)
        {
            emit SIG_GOBACKTOMENU();
        }
        break;
    default:
        break;
    }
}
