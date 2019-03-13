/*
* C++ && Qt Tetris: Window Tetrix Board
* Author: walid Abbassi [https://github.com/walidAbbassi]
* 2019
*
* Source code is licensed under MIT License
* (for more details see LICENSE)
*
*/
#include "precompiledHeader.h"
#include "tetrixboard.h"

/*
*	Constructor Tetrix Board
*	@name	: TetrixBoard
*	@param	: QWidget
*	@return : void
*/
TetrixBoard::TetrixBoard(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();
    player.setMedia(QUrl("qrc:/sound/Tetris.mp3"));
    player.setVolume(volume);

    nextPiece.setRandomShape();
}

/*
*	Set Next Piece Label
*	@name	: setNextPieceLabel
*	@param	: QLabel.
*	@return : void
*/
void TetrixBoard::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}

/*
*	Resize frame
*	@name	: sizeHint
*	@param	: no param.
*	@return : QSize
*/
QSize TetrixBoard::sizeHint() const
{
    return QSize(BoardWidth * 15 + frameWidth() * 2,
                 BoardHeight * 15 + frameWidth() * 2);
}

/*
*	Minimum Size frame
*	@name	: minimumSizeHint
*	@param	: no param.
*	@return : QSize
*/
QSize TetrixBoard::minimumSizeHint() const
{
    return QSize(BoardWidth * 5 + frameWidth() * 2,
                 BoardHeight * 5 + frameWidth() * 2);
}

/*
*	Start Game
*	@name	: start
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::start()
{
    if (isPaused)
        return;

    player.play();
    isStarted = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    level = 1;
    volume = 50;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);
    player.setVolume(volume);
    pieceSound.setVolume(volume);

    newPiece();
    timer.start(timeoutTime(), this);
}

/*
*	Pause Game
*	@name	: pause
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
        player.pause();
    } else {
        timer.start(timeoutTime(), this);
        player.play();
    }
    update();
}

/*
*	Set Volume Game
*	@name	: setVolume
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::setVolume(int volume)
{
    if(volume == 0)
    {
        player.setMuted(true);
        pieceSound.setMuted(true);
    }
    else{
        player.setMuted(false);
        player.setVolume(volume);
        pieceSound.setMuted(false);
        pieceSound.setVolume(volume);
    }
}

/*
*	paint Event in frame
*	@name	: paintEvent
*	@param	: QPaintEvent.
*	@return : void
*/
void TetrixBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();

    if (isPaused) {
        painter.setPen ( Qt::white );
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }

    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
            if (shape != NoShape)
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), shape);
        }
    }

    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + (BoardHeight - y - 1) * squareHeight(),
                       curPiece.shape());
        }
    }
    if(player.state()== QMediaPlayer::StoppedState)
    {
        player.play();
    }
}

/*
*	key Press Event
*	@name	: keyPressEvent
*	@param	: QKeyEvent
*	@return : void
*/
void TetrixBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_Down:
        tryMove(curPiece.rotatedRight(), curX, curY);
        break;
    case Qt::Key_Up:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Qt::Key_Space:
        dropDown();
        break;
    case Qt::Key_D:
        oneLineDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

/*
*	timer Event
*	@name	: timerEvent
*	@param	: QKeyEQTimerEventvent
*	@return : void
*/
void TetrixBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

/*
*	clear Board TetrixShape
*	@name	: clearBoard
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}

/*
*	Drop Down current TetrixPiece
*	@name	: dropDown
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
}

/*
*	Drop Down by one Line the current TetrixPiece
*	@name	: oneLineDown
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}

/*
*	piece is Dropped : update score/level/removeFullLines
*	@name	: pieceDropped
*	@param	: int dropHeight
*	@return : void
*/
void TetrixBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }
    pieceSound.setMedia(QUrl("qrc:/sound/drop.wav"));
    pieceSound.play();
    ++numPiecesDropped;
    if (numPiecesDropped % 25 == 0) {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight + 7;
    emit scoreChanged(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
}


/*
*	remove Full Lines from bord
*	@name	: removeFullLines
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            ++numFullLines;
            pieceSound.setMedia(QUrl("qrc:/sound/money.wav"));
            pieceSound.play();
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
        }
    }

    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        update();
    }
}

/*
*	make new TetrixPiece
*	@name	: newPiece
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + curPiece.minY();

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
    }
}

/*
*	show next TetrixPiece
*	@name	: showNextPiece
*	@param	: no param.
*	@return : void
*/
void TetrixBoard::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(),
                   nextPiece.shape());
    }
    nextPieceLabel->setPixmap(pixmap);
}

/*
*	Move TetrixPiece
*	@name	: tryMove
*	@param	: TetrixPiece, int X, int Y
*	@return : bool
*/
bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

/*
*	draw TetrixPiece
*	@name	: drawSquare
*	@param	: QPainter, int x, int y, TetrixShape
*	@return : void
*/
void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
