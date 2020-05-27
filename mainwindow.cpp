#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, QWidget *_another) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    another = _another;
    //_another->setWindowState(Qt::WindowFullScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    another->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::on_pushButton_2_clicked()
{
    websocket->m_webSocket.sendTextMessage(QStringLiteral("Hello, world~~~"));
}

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}
