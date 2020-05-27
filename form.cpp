#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *_windows[3]) :
    ui(new Ui::Form)
{
    ui->setupUi(this);
    windows = _windows;
}

Form::~Form()
{
    delete ui;
}


void Form::on_pushButton_clicked()
{
    setWindowState(Qt::WindowMaximized);
}

void Form::on_pushButton_2_clicked()
{
    windows[1]->hide(); // hide main window
}

void Form::on_pushButton_3_clicked()
{
    windows[1]->show(); // show main window
    //MainWindow->raise(); // bring to top/front.
}
