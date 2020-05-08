#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "container.h"
#include "position.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addPos_clicked();

    void on_delPos_clicked();

    void on_pushButton_clicked();

    void on_swapPos_clicked();

    void on_setChanges_clicked();

private:
    Ui::MainWindow *ui;

    //QList<Position> listPos;

    QList<Container> listCont;
};

#endif // MAINWINDOW_H
