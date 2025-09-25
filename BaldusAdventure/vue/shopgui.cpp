#include "shopgui.h"
#include <QPainter>
void ShopGui::setIsKeyChanging(bool newIsKeyChanging)
{
    isKeyChanging = newIsKeyChanging;
}

int ShopGui::getActualPage() const
{
    return actualPage;
}

ShopType ShopGui::getItscurrentSelection() const
{
    return itscurrentSelection;
}

ShopGui::ShopGui(QWidget *parent) : QWidget(parent)
{

}

void ShopGui::paintEvent(QPaintEvent *e)
{
    QPixmap image;
    switch(actualPage){
    case 1:
        image = QPixmap(":/menu/images/menus/Shop_Weak.png");
        break;
    case 2:
        image = QPixmap(":/menu/images/menus/Shop_Average.png");
        break;
    case 3:
        image = QPixmap(":/menu/images/menus/Shop_Strong.png");
        break;
    default:
        break;
    }
    if(itscurrentSelection == WEAKPAGE || itscurrentSelection == AVERAGEPAGE || itscurrentSelection == STRONGPAGE || itscurrentSelection == ESC)
        isKeyChanging=false;

    QPainter aPainter(this);

    if(!image.isNull())
    {
        aPainter.drawPixmap(0,0,width(), height(),image);
    }
    else
    {
        throw std::string("Failed to load the menu Picture");
    }
    if(isKeyChanging)
        aPainter.setPen(QPen(QColorConstants::Svg::orange,2));
    else {
        aPainter.setPen(QPen(Qt::yellow,2));
    }
    switch (itscurrentSelection) {
    case SPELLUPLEFT:
        aPainter.drawRect(width()*0.096,height()*0.418,width()*0.405, height()*0.207);
        break;
    case SPELLUPRIGHT:
        aPainter.drawRect(width()*0.50,height()*0.418,width()*0.405, height()*0.207);
        break;
    case SPELLDOWNLEFT:
        aPainter.drawRect(width()*0.096,height()*0.65,width()*0.405, height()*0.207);
        break;
    case SPELLDOWNRIGHT:
        aPainter.drawRect(width()*0.5,height()*0.65,width()*0.405, height()*0.207);
        break;
    case WEAKPAGE:
        aPainter.drawRect(width()*0.11,height()*0.28,width()*0.247, height()*0.133);
        break;
    case AVERAGEPAGE:
        aPainter.drawRect(width()*0.38,height()*0.28,width()*0.247, height()*0.133);
        break;
    case STRONGPAGE:
        aPainter.drawRect(width()*0.64,height()*0.28,width()*0.247, height()*0.133);
        break;
    case ESC:
        aPainter.drawRect(width()*0.76,height()*0.13,width()*0.098, height()*0.132);
        break;
    default:
        break;
    }
}

void ShopGui::updateSelection(int aDirection)
{
    //1 = UP, 2 = down, 3 = left, 4 =: right, 5 = enter
    if(isKeyChanging == false)
    {
        switch (itscurrentSelection) {
        case SPELLUPLEFT:
            if(aDirection == 1)
            {
                itscurrentSelection = WEAKPAGE;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = SPELLDOWNLEFT;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = SPELLUPRIGHT;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = SPELLUPRIGHT;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
            }
            break;
        case SPELLUPRIGHT:
            if(aDirection == 1)
            {
                itscurrentSelection = STRONGPAGE;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = SPELLDOWNRIGHT;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = SPELLUPLEFT;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = SPELLUPLEFT;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
            }
            break;
        case SPELLDOWNLEFT:
            if(aDirection == 1)
            {
                itscurrentSelection = SPELLUPLEFT;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = WEAKPAGE;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = SPELLDOWNRIGHT;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = SPELLDOWNRIGHT;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
            }
            break;
        case SPELLDOWNRIGHT:
            if(aDirection == 1)
            {
                itscurrentSelection = SPELLUPRIGHT;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = ESC;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = SPELLDOWNLEFT;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = SPELLDOWNLEFT;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
            }
            break;
        case WEAKPAGE:
            if(aDirection == 1)
            {
                itscurrentSelection = SPELLDOWNLEFT;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = SPELLUPLEFT;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = STRONGPAGE;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = AVERAGEPAGE;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
                actualPage = 1;
            }
            break;
        case AVERAGEPAGE:
            if(aDirection == 1)
            {
                itscurrentSelection = SPELLDOWNLEFT;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = SPELLUPLEFT;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = WEAKPAGE;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = STRONGPAGE;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
                actualPage = 2;
            }
            break;
        case STRONGPAGE:
            if(aDirection == 1)
            {
                itscurrentSelection = ESC;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = SPELLUPRIGHT;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = AVERAGEPAGE;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = WEAKPAGE;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
                actualPage = 3;
            }
            break;
        case ESC:
            if(aDirection == 1)
            {
                itscurrentSelection = SPELLDOWNRIGHT;
            }
            else if(aDirection == 2)
            {
                itscurrentSelection = STRONGPAGE;
            }
            else if(aDirection == 3)
            {
                itscurrentSelection = ESC;
            }
            else if(aDirection == 4)
            {
                itscurrentSelection = ESC;
            }
            else if(aDirection == 5)
            {
                isKeyChanging = true;
                emit SIG_SHOPCLOSE();
            }
            break;
        default:
            break;
        }
    }
}
