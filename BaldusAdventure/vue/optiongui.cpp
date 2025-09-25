#include "optiongui.h"


#include <QPixmap>




OptionGui::OptionGui(QWidget *parent, SettingType aSetting, bool aSoundMuted)
    : QWidget(parent), itscurrentSetting(aSetting), isSoundMuted(aSoundMuted)
{}

void OptionGui::paintEvent(QPaintEvent *e)
{
    QPixmap image(":/menu/images/menus/option.png");
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

    isKeyChanging?aPainter.setPen(QPen(QColorConstants::Svg::orange,2)):aPainter.setPen(QPen(Qt::yellow,2));

    switch (itscurrentSetting) {
    case SPELL1:
        aPainter.drawRect(width()*0.175,height()*0.39,width()*0.23, height()*0.13);
        break;
    case SPELL2:
        aPainter.drawRect(width()*0.175,height()*0.535,width()*0.23, height()*0.135);
        break;
    case UP:
        aPainter.drawRect(width()*0.672,height()*0.465,width()*0.212, height()*0.135);
        break;
    case LEFT:
        aPainter.drawRect(width()*0.41,height()*0.39,width()*0.257, height()*0.135);
        break;
    case RIGHT:
        aPainter.drawRect(width()*0.41,height()*0.535,width()*0.257, height()*0.135);
        break;
    case BACK:
        aPainter.drawRect(width()*0.707,height()*0.112,width()*0.0915, height()*0.135);
        break;
    case SOUND:
        aPainter.drawRect(width()*0.484,height()*0.687,width()*0.111, height()*0.135);
        break;
    default:
        break;
    }

    if(isSoundMuted)
    {
        aPainter.setPen(QPen(Qt::red,4));
        aPainter.drawLine(width()*0.494,height()*0.812,width()*0.585,height()*0.697);
    }

    drawKeys(&aPainter);
}

void OptionGui::updateSetting(int aDirection)
{
    //1 = UP, 2 = down, 3 = left, 4 =: right, 5 = enter
    switch (itscurrentSetting) {
    case SPELL1:
        if(aDirection == 1)
        {
            itscurrentSetting = BACK;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = SPELL2;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = LEFT;
        }
        else if(aDirection == 5)
        {
            isKeyChanging = true;
        }
        break;
    case SPELL2:
        if(aDirection == 1)
        {
            itscurrentSetting = SPELL1;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = SOUND;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = RIGHT;
        }
        else if(aDirection == 5)
        {
            isKeyChanging = true;
        }
        break;
    case UP:
        if(aDirection == 1)
        {
            itscurrentSetting = BACK;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = SOUND;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = LEFT;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = SPELL1;
        }
        else if(aDirection == 5)
        {
            isKeyChanging = true;
        }
        break;
    case LEFT:
        if(aDirection == 1)
        {
            itscurrentSetting = BACK;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = RIGHT;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = SPELL1;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 5)
        {
            isKeyChanging = true;
        }
        break;
    case RIGHT:
        if(aDirection == 1)
        {
            itscurrentSetting = LEFT;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = SOUND;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = SPELL2;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 5)
        {
            isKeyChanging = true;
        }
        break;
    case BACK:
        if(aDirection == 1)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = LEFT;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = SPELL1;
        }
        else if(aDirection == 5)
        {
            //to add, emit un signal pour fermer le menu
            emit SIG_OPTIONCLOSE();
        }
        break;
    case SOUND:
        if(aDirection == 1)
        {
            itscurrentSetting = RIGHT;
        }
        else if(aDirection == 2)
        {
            itscurrentSetting = LEFT;
        }
        else if(aDirection == 3)
        {
            itscurrentSetting = SPELL2;
        }
        else if(aDirection == 4)
        {
            itscurrentSetting = UP;
        }
        else if(aDirection == 5)
        {
            //to add, changer le son
            emit SIG_MUTESOUND();
            isSoundMuted?isSoundMuted = false: isSoundMuted = true;
        }
        break;
    default:
        break;
    }
}


/**
 * @brief Converts a Qt::Key to a readable string for display.
 *
 * Special keys are mapped to icons or abbreviations (e.g., arrows, "esc").
 * Alphanumeric keys are truncated if needed.
 *
 * @param key The Qt key to convert.
 * @return A string representation suitable for the UI.
 */
QString keyToDisplay(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Space:        return "esp";
    case Qt::Key_Right:        return "→";
    case Qt::Key_Left:         return "←";
    case Qt::Key_Up:           return "↑";
    case Qt::Key_Down:         return "↓";
    case Qt::Key_Backspace:    return "⌫";
    case Qt::Key_Delete:       return "⌦";
    case Qt::Key_Enter:        return "↵";
    case Qt::Key_Return:       return "↵";
    case Qt::Key_Escape:       return "esc";
    case Qt::Key_Control:      return "ctrl";
    case Qt::Key_Shift:        return "shift";
    case Qt::Key_Alt:          return "alt";
    case Qt::Key_Tab:          return "tab";
    case Qt::Key_CapsLock:     return "cap";
    case Qt::Key_PageUp:       return "⇟";
    case Qt::Key_PageDown:     return "⇞";
    case Qt::Key_Home:         return "↖";
    case Qt::Key_End:          return "↘";
    case Qt::Key_Insert:       return "ins";
    case Qt::Key_Menu:         return "men";
    case Qt::Key_Super_L:      return "⊞";
    default:

        QString aKey = QKeySequence(key).toString();

        if(aKey.size() > 3)
        {
            aKey = aKey.left(3);
        }


        return aKey;
    }
}



void OptionGui::drawKeys(QPainter *aPainter)
{

    aPainter->setPen(QColor::fromRgb(133,66,54));
    aPainter->setFont(QFont("Courier New",15*width()/1000,QFont::Bold));


    // Exemple : affichage des touches liées aux actions
    aPainter->drawText(width()*0.337, height()*0.477, keyToDisplay(itsSpellOneKey));
    aPainter->drawText(width()*0.337, height()*0.625, keyToDisplay(itsSpellTwoKey));
    aPainter->drawText(width()*0.81, height()*0.552, keyToDisplay(itsGoUpKey));
    aPainter->drawText(width()*0.6, height()*0.477, keyToDisplay(itsGoLeftKey));
    aPainter->drawText(width()*0.6, height()*0.625, keyToDisplay(itsGoRightKey));

}

void OptionGui::setKeys(Qt::Key aSpellOneKey,
                        Qt::Key aSpellTwoKey,
                        Qt::Key aGoUpKey,
                        Qt::Key aGoLeftKey,
                        Qt::Key aGoRightKey)
{
    itsSpellOneKey= aSpellOneKey;
    itsSpellTwoKey= aSpellTwoKey;
    itsGoUpKey= aGoUpKey;
    itsGoLeftKey= aGoLeftKey;
    itsGoRightKey= aGoRightKey;

    isKeyChanging = false;
}

bool OptionGui::getIsKeyChanging() const
{
    return isKeyChanging;
}

void OptionGui::setIsKeyChanging(bool newIsKeyChanging)
{
    isKeyChanging = newIsKeyChanging;
}

void OptionGui::setOneKey(SettingType aSetting, Qt::Key aKey)
{
    // SPELL1,
    //     SPELL2,
    //     UP,
    //     DOWN,
    //     LEFT,
    //     RIGHT,
    //     RETURN,
    switch (aSetting) {
    case SPELL1:
        itsSpellOneKey = aKey;
        break;
    case SPELL2:
        itsSpellTwoKey = aKey;
        break;
    case UP:
        itsGoUpKey = aKey;
        break;
    case LEFT:
        itsGoLeftKey = aKey;
        break;
    case RIGHT:
        itsGoRightKey = aKey;
        break;
    default:
        break;
    }

    isKeyChanging = false;
}


SettingType OptionGui::getItscurrentSetting() const
{
    return itscurrentSetting;
}
