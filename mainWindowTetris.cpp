/*
* C++ && Qt Tetris: Window Tetris
* Author: walid Abbassi [https://github.com/walidAbbassi]
* 2019
*
* Source code is licensed under MIT License
* (for more details see LICENSE)
*
*/
#include <QMessageBox>
#include <QHBoxLayout>
#include <QIcon>

#include "mainWindowTetris.h"
#include "ui_mainWindowTetris.h"
#include "tetrixwindow.h"

/*
*	constructor Main Window Tetris
*	@name	: MainWindowTetris
*	@param	: QWidget
*	@return : void
*/
MainWindowTetris::MainWindowTetris(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowTetris)
{
    ui->setupUi(this);
	TetrixWindow *window = new TetrixWindow;
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(window);
	setCentralWidget(new QWidget);
	centralWidget()->setLayout(layout);
    setFixedSize(500, 670);
	this->setWindowTitle("Qt Tetris");
	this->setWindowIcon(QIcon(":/picture/tetris.png"));
    createMenuBar();
}

/*
*	create MenuBar for parent widget
*	@name	: createMenuBar
*	@param	: no param.
*	@return : void
*/
void MainWindowTetris::createMenuBar()
{
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&commande"), this, &MainWindowTetris::commande);
    aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindowTetris::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
}

/*
*	create MessageBox for control key tetris 
*	@name	: commande
*	@param	: no param.
*	@return : void
*/
void MainWindowTetris::commande()
{
   QMessageBox::about(this, tr("commande Game"),
            tr("<br><b>key → :</b>  move left \n</br>"
               "<br><b>key ← :</b>  move right \n</br>"
               "<br><b>key ↓ :</b>  rotate right \n</br>"
               "<br><b>key ↑ :</b>  rotate left \n</br>"
               "<br><b>key space :</b>  drop down \n</br>"
               "<br><b>key D :</b>  drop one line down</br>"));
}

/*
*	create MessageBox about tetris application
*	@name	: about
*	@param	: no param.
*	@return : void
*/
void MainWindowTetris::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write Tetris game using Qt "
               " (Have fun walid abbassi)."));
}

/*
*	destructor Main Window Tetris
*	@name	: ~MainWindowTetris
*	@param	: no param.
*	@return : void
*/
MainWindowTetris::~MainWindowTetris()
{
    delete ui;
}
