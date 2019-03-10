/********************************************************************************
** Form generated from reading UI file 'mainWindowTetris.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWTETRIS_H
#define UI_MAINWINDOWTETRIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowTetris
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowTetris)
    {
        if (MainWindowTetris->objectName().isEmpty())
            MainWindowTetris->setObjectName(QStringLiteral("MainWindowTetris"));
        MainWindowTetris->resize(400, 460);
        centralWidget = new QWidget(MainWindowTetris);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowTetris->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowTetris);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        MainWindowTetris->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowTetris);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowTetris->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowTetris);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowTetris->setStatusBar(statusBar);

        retranslateUi(MainWindowTetris);

        QMetaObject::connectSlotsByName(MainWindowTetris);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowTetris)
    {
        MainWindowTetris->setWindowTitle(QApplication::translate("MainWindowTetris", "MainWindowTetris", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowTetris: public Ui_MainWindowTetris {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWTETRIS_H
