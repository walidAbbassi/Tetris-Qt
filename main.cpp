#include "mainWindowTetris.h"
#include <QApplication>


#include <stdlib.h>
#include "tetrixwindow.h"

int main(int argc, char *argv[])
{
    QApplication applicationTetris(argc, argv);
    MainWindowTetris windowTetris;

    windowTetris.show();

    return applicationTetris.exec();
}
