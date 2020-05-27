#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "websocket.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *_windows[3] = nullptr);
    ~MainWindow();

    WebSocket *websocket;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QWidget **windows;
};

#endif // MAINWINDOW_H
