#include "losenwingui.h"
#include <QPainter>

LoseNWinGui::LoseNWinGui(QWidget *parent,
                         bool aGameWon,
                         int aScore,
                         int aTime,
                         QPixmap aWinPixmap ,
                         QPixmap aLosePixmap)
    :QWidget(parent), itsWinPixMap(aWinPixmap), itsLosePixmap(aLosePixmap), itsGameWon(aGameWon), itsScore(aScore), itsTime(aTime)
{}

void LoseNWinGui::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter aPainter(this);

    aPainter.drawPixmap(0,0,width(), height(),itsGameWon?itsWinPixMap:itsLosePixmap);

    aPainter.setPen(Qt::white);
    aPainter.setFont(QFont("", 29,700));

    aPainter.drawText(width()/2-100, height()/2+60,QString("Score : ")+ QString::number(itsScore));
    if(itsGameWon)
    {
        QString tempTime = QString::number(itsTime / 60000) + " : ";
        if ((itsTime % 60000) / 1000 < 10)
            tempTime += "0";
        tempTime += QString::number((itsTime % 60000) / 1000);
        aPainter.drawText(width()/2-115, height()/2+70+29,QString("Temps  ")+QString(tempTime)+QString(" s"));
    }
}
