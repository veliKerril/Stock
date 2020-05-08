#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon/img/stockIcon.com.png"));
    //this->setWindowFlags(Qt::FramelessWindowHint);
}

StartWindow::~StartWindow()
{
    delete ui;
}


void StartWindow::on_pushButton_clicked()
{
    this->close();
    mainWindow = new MainWindow();
    mainWindow->show();
}
