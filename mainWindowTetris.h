#ifndef MAINWINDOWTETRIS_H
#define MAINWINDOWTETRIS_H

#include <QMainWindow>

namespace Ui {
class MainWindowTetris;
}

class MainWindowTetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowTetris(QWidget *parent = nullptr);
    ~MainWindowTetris();

private:
    Ui::MainWindowTetris *ui;
    void createMenuBar();

private slots:
    void commande();
    void about();

};

#endif // MAINWINDOWTETRIS_H
