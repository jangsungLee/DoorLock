#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *_windows[3]) :
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windows = _windows;
    //_another->setWindowState(Qt::WindowFullScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    windows[2]->setWindowState(Qt::WindowFullScreen); // set form WindowFullScreen
}

void MainWindow::on_pushButton_2_clicked()
{
    websocket->m_webSocket.sendTextMessage(QStringLiteral("Hello, world~~~"));
}

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}
