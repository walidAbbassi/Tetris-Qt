/*
* C++ && Qt Tetris: main application
* Author: walid Abbassi [https://github.com/walidAbbassi]
* 2019
*
* Source code is licensed under MIT License
* (for more details see LICENSE)
*
*/
#include "precompiledHeader.h"
#include "mainWindowTetris.h"
#include "tetrixwindow.h"

int main(int argc, char *argv[])
{
    QApplication applicationTetris(argc, argv);
    MainWindowTetris windowTetris;
    windowTetris.show();
    return applicationTetris.exec();
}
