#include "mainWindowTetris.h"
#include "ui_mainWindowTetris.h"
#include <QHBoxLayout>
#include "tetrixwindow.h"
#include <QIcon>
#include <QMessageBox>

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

void MainWindowTetris::createMenuBar()
{
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&commande"), this, &MainWindowTetris::commande);
    aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindowTetris::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
}

void MainWindowTetris::commande()
{
//    QString s = QChar(&#x2B06;);
   QMessageBox::about(this, tr("commande Game"),
            tr("<br><b>key → :</b>  move left \n</br>"
               "<br><b>key ← :</b>  move right \n</br>"
               "<br><b>key ↓ :</b>  rotate right \n</br>"
               "<br><b>key ↑ :</b>  rotate left \n</br>"
               "<br><b>key space :</b>  drop down \n</br>"
               "<br><b>key D :</b>  drop one line down</br>"));
}

void MainWindowTetris::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write Tetris game using Qt "
               " (Have fun walid abbassi)."));
}

MainWindowTetris::~MainWindowTetris()
{
    delete ui;
}
