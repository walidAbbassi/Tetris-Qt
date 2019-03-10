#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>
#include <QDial>

class QLCDNumber;
class QLabel;
class QPushButton;

class TetrixBoard;

class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
    TetrixWindow();

private:
    QLabel *createLabel(const QString &text);

    TetrixBoard *board;
    QLabel *nextPieceLabel;
    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
    QDial *volumeDial;
};
#endif // TETRIXWINDOW_H
