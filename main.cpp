#include "mainWindowTetris.h"
#include <QApplication>


#include <stdlib.h>
#include "tetrixwindow.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    //MainWindowTetris w;
    //w.show();

//    return a.exec();

    QApplication app(argc, argv);
    //TetrixWindow window;
    //window.show();
    MainWindowTetris w;

	w.show();

    return app.exec();
}
