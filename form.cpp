#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::addMainWindow(QMainWindow *target)
{
    MainWindow = target;
}

void Form::on_pushButton_clicked()
{
    setWindowState(Qt::WindowMaximized);
}

void Form::on_pushButton_2_clicked()
{
    MainWindow->hide();
}

void Form::on_pushButton_3_clicked()
{
    MainWindow->show();
    //MainWindow->raise(); // bring to top/front.
}
