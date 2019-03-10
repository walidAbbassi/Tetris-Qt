#include <QtWidgets>

#include "tetrixboard.h"
#include "tetrixwindow.h"

TetrixWindow::TetrixWindow()
{
    board = new TetrixBoard;

    nextPieceLabel = new QLabel;
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    board->setNextPieceLabel(nextPieceLabel);
    board->setStyleSheet("background-image: url(:/picture/background.jpg);");

    scoreLcd = new QLCDNumber(2);
    scoreLcd->setSegmentStyle(QLCDNumber::Outline);
    scoreLcd->setStyleSheet("background-color: black");
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Outline);
    levelLcd->setStyleSheet("background-color: black");
    linesLcd = new QLCDNumber(2);
    linesLcd->setSegmentStyle(QLCDNumber::Outline);
    linesLcd->setStyleSheet("background-color: black");

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    volumeDial = new QDial();
    volumeDial->setFocusPolicy(Qt::StrongFocus);
    volumeDial->setNotchesVisible(true);
    volumeDial->setMaximum(100);
    volumeDial->setMinimum(0);
    volumeDial->setValue(50);
    volumeDial->setStyleSheet("QDial{ background-color: "
                              "QLinearGradient(spread:pad, x1:0.683, y1:1, x2:1, y2:0,"
                              " stop:0 rgba(103, 103, 103,255), stop:1 rgba(144, 144, 144, 255)); }");

    connect(startButton, &QPushButton::clicked, board, &TetrixBoard::start);
    connect(quitButton , &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &TetrixBoard::pause);
    connect(volumeDial, SIGNAL(valueChanged(int)),board, SLOT(setVolume(int))); //lazy
#if __cplusplus >= 201402L
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, QOverload<int>::of(&QLCDNumber::display));
#endif

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(board, 0, 0, 15, 8);
	layout->addWidget(createLabel(tr("NEXT")), 0, 9);
	layout->addWidget(nextPieceLabel, 1, 9);
	layout->addWidget(createLabel(tr("LEVEL")), 2, 9);
	layout->addWidget(levelLcd, 3, 9);
    layout->addWidget(createLabel(tr("SCORE")), 4, 9);
    layout->addWidget(scoreLcd, 5, 9);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 6, 9);
    layout->addWidget(linesLcd, 7, 9);
	layout->addWidget(createLabel(tr("    ")), 8, 9);
    layout->addWidget(quitButton, 9, 9);
    layout->addWidget(pauseButton, 10, 9);
	layout->addWidget(startButton, 11, 9);
    layout->addWidget(volumeDial, 14, 9);
    setLayout(layout);
}

QLabel *TetrixWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
