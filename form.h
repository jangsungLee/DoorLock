#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *_windows[3] = nullptr);
    ~Form();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Form *ui;

    QWidget **windows;

    bool isOn = false;
};

#endif // FORM_H
