#include "gamewindow.h"
#include "welcomescreen.h"
#include <QApplication>
#include <QDesktopWidget>
//#include "world.h"

int main(int argc, char *argv[])
{
/*
    QApplication app(argc, argv);
    World world;
    world.setFixedSize(1000, 580);
    world.show();
    world.start();
    world.setFocusPolicy(Qt::StrongFocus);
    return app.exec();*/


    QApplication a(argc, argv);
    //GameWindow w;
    WelcomeScreen w;
    w.show();

    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    return a.exec();

}
