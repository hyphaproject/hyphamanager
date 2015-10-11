#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QSplashScreen(parent)
{
    setPixmap(QPixmap(":/main/hypha_text"));
}

void SplashScreen::setMessage(QString message){
    showMessage(message, Qt::AlignBottom | Qt::AlignLeft, Qt::blue);
}
