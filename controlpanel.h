#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QPalette>
#include <QTimer>
#include <QHostAddress>
#include <QNetworkInterface>
#ifdef __linux__
#include <pigpio.h>
#endif

#define BUBL1 25
#define BUBL2 8
#define BUBL3 7
#define BUBL4 1
#define BUBL5 12
#define BUBL6 16
#define BUBL7 20
#define BUBL8 21

#define HOT_BUBL1 24
#define HOT_BUBL2 23
#define HOT_BUBL3 18

#define WATER_PUMP_FB_SIGNAL 15
#define WATER_PUMP_PWM 14

#define DOORLOC_MOTOR_FB_SIGNAL 26
#define DOORLOC_MOTOR_PWM 19
#define DOORLOC_CHECK_OPEN_SW 6
#define DOORLOC_CHECK_CLOSE_SW 5

#define PIN_HIGH 1
#define PIN_LOW 0

#define PDLC_PIN 13

#define MOTOR_FORWARD 0
#define MOTOR_BACKWARD 1

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

    int ButtonControl(QString button_name);

    bool isOn_bubls = false, isOn_hotBubls = false, isOn_PDLC = false, isOn_waterPump = false, isOn_doorMotor = false;
    bool isOn_bulb1 = false, isOn_bulb2 = false, isOn_bulb3 = false, isOn_bulb4 = false, isOn_bulb5 = false, isOn_bulb6 = false, isOn_bulb7 = false, isOn_bulb8 = false;
    bool isOn_hotBulb1 = false, isOn_hotBulb2 = false, isOn_hotBulb3 = false;
    bool isDoorOpen = false, isIgnoreOpenSW_Status = false, isIgnoreCloseSW_Status = false;
    int currentWaterPower = 100, currentDoorPower = 100;

private slots:

    void on_pushButton_bulbs_clicked();

    void on_pushButton_hotBulbs_clicked();

    void on_pushButton_PDLC_clicked();

    void on_pushButton_waterPump_clicked();

    void on_pushButton_doorMotor_clicked();

    void on_horizontalSlider_waterPumpSlider_valueChanged(int value);

    void on_horizontalSlider_doorLock_valueChanged(int value);

    void OnTimerCallbackFunc_CheckDoorOpen();
    void OnTimerCallbackFunc_CheckDoorClose();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::ControlPanel *ui;

    QTimer *m_pTimerO, *m_pTimerC;
    int checkSW_time = 250;
};

#endif // CONTROLPANEL_H
