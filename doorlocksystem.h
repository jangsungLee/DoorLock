#ifndef DOORLOCKSYSTEM_H
#define DOORLOCKSYSTEM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class DoorLockSystem;
}

class DoorLockSystem : public QWidget
{
    Q_OBJECT

public:
    explicit DoorLockSystem(QWidget *_windows[3] = nullptr);
    ~DoorLockSystem();

    Ui::DoorLockSystem *ui;
private slots:
    void on_pushButton_19_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void OnTimerCallbackFunc();

private:
    QWidget **windows;
    const char encrypted_character = '*';
    const int display_count = 10, resetTime = 5000/*5s*/;
    int number_index = 0;
    char input_value[20] = {0}, display_letters[20] {0};
    const char *systemSetting = "*#0#*", *changePassword = "*123*", *initialPassword = "0000";
    char password[20];

    QTimer *m_pTimer;

    void Clear();
    void changeInitImage();
};

#endif // DOORLOCKSYSTEM_H
