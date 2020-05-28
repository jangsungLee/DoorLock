#include "controlpanel.h"
#include "ui_controlpanel.h"

#include <QtDebug>

#define BUBLS "Bubls"
#define HOT_BUBLS "Hot_Bubls"
#define PDLC "PDLC"
#define WATER_PUMP "Water_Pump"
#define DOOR_MOTOR "Door_Motor"

void makeButtonOff(QPushButton *buttonPointer, QPalette pal)
{
    pal.setColor(QPalette::Button, QColor(Qt::transparent));
    buttonPointer->setPalette(pal);
}
void makeButtonOn(QPushButton *buttonPointer, QPalette pal)
{
    pal.setColor(QPalette::Button, QColor(181, 217, 232));
    buttonPointer->setPalette(pal);
}

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    ui->horizontalSlider_waterPumpSlider->setValue(currentWaterPower);
    ui->horizontalSlider_doorLock->setValue(currentDoorPower);

    QString ipAddressAll = "*** My Interface IP Address ***\n";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {

            ipAddressAll += address.toString() + "\n";
        }
        else
        {

        }

    }
    ui->Qlabel_IPADDRESS->setText(ipAddressAll);

    m_pTimerO = new QTimer();
    m_pTimerC = new QTimer();
    connect(m_pTimerO, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc_CheckDoorOpen()));
    connect(m_pTimerO, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc_CheckDoorClose()));
    m_pTimerO->start(checkSW_time);
    m_pTimerC->start(checkSW_time);



#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)
   //#ifdef _WIN64
      //define something for Windows (64-bit only)
   //#endif
    qDebug() << "iT's Windows";


#elif __linux__
    // linux
    qDebug() << "iT's linux, I'm Targeted at Raspberry Pi";


//#elif __unix__ // all unices not caught above
    // Unix

//#elif defined(_POSIX_VERSION)
    // POSIX

#else
#   error "Unknown compiler"
#endif
}

ControlPanel::~ControlPanel()
{
    delete ui;
}



void ControlPanel::on_pushButton_bulbs_clicked() // 전구
{
    ButtonControl(BUBLS);
}

void ControlPanel::on_pushButton_hotBulbs_clicked() // 열전구
{
    ButtonControl(HOT_BUBLS);
}

void ControlPanel::on_pushButton_PDLC_clicked() // PDLC
{
    ButtonControl(PDLC);
}

void ControlPanel::on_horizontalSlider_waterPumpSlider_valueChanged(int value) // Slider : 물펌프
{
#ifdef __linux__
    gpioPWM(WATER_PUMP_PWM, value);
    currentWaterPower = value;
#endif
}

void ControlPanel::on_pushButton_waterPump_clicked() // 물펌프
{
    ButtonControl(WATER_PUMP);
}

void ControlPanel::on_horizontalSlider_doorLock_valueChanged(int value) // Slider : 도어락
{
#ifdef __linux__
    gpioPWM(DOORLOC_MOTOR_PWM, value);
    currentDoorPower = value;
#endif
}

void ControlPanel::on_pushButton_doorMotor_clicked() // 도어락
{
    ButtonControl(DOOR_MOTOR);
}

int ControlPanel::ButtonControl(QString button_name)
{
    QPushButton *buttonPointer = nullptr;
    QPalette pal;

    if(button_name == BUBLS)
    {
        isOn_bubls = !isOn_bubls;
        isOn_bulb1 = !isOn_bulb1;
        isOn_bulb2 = !isOn_bulb2;
        isOn_bulb3 = !isOn_bulb3;
        isOn_bulb4 = !isOn_bulb4;
        isOn_bulb5 = !isOn_bulb5;
        isOn_bulb6 = !isOn_bulb6;
        isOn_bulb7 = !isOn_bulb7;
        isOn_bulb8 = !isOn_bulb8;

        buttonPointer = ui->pushButton_bulbs;
        pal = buttonPointer->palette();

        if(isOn_bubls)
        {
            // make turn off
            makeButtonOff(buttonPointer, pal);
#ifdef __linux__
            gpioWrite(BUBL1, PIN_LOW);
            gpioWrite(BUBL2, PIN_LOW);
            gpioWrite(BUBL3, PIN_LOW);
            gpioWrite(BUBL4, PIN_LOW);
            gpioWrite(BUBL5, PIN_LOW);
            gpioWrite(BUBL6, PIN_LOW);
            gpioWrite(BUBL7, PIN_LOW);
            gpioWrite(BUBL8, PIN_LOW);
#endif
        }
        else
        {
            // make turn on
            makeButtonOn(buttonPointer, pal);
#ifdef __linux__
            gpioWrite(BUBL1, PIN_HIGH);
            gpioWrite(BUBL2, PIN_HIGH);
            gpioWrite(BUBL3, PIN_HIGH);
            gpioWrite(BUBL4, PIN_HIGH);
            gpioWrite(BUBL5, PIN_HIGH);
            gpioWrite(BUBL6, PIN_HIGH);
            gpioWrite(BUBL7, PIN_HIGH);
            gpioWrite(BUBL8, PIN_HIGH);
#endif
        }
    }
    else if(button_name == HOT_BUBLS)
    {
        isOn_hotBubls = !isOn_hotBubls;
        isOn_hotBulb1 = !isOn_hotBulb1;
        isOn_hotBulb2 = !isOn_hotBulb2;
        isOn_hotBulb3 = !isOn_hotBulb3;

        buttonPointer = ui->pushButton_hotBulbs;
        pal = buttonPointer->palette();

        if(isOn_hotBubls)
        {
            // make turn off
            makeButtonOff(buttonPointer, pal);
#ifdef __linux__
           gpioWrite(HOT_BUBL1, PIN_LOW);
           gpioWrite(HOT_BUBL2, PIN_LOW);
           gpioWrite(HOT_BUBL3, PIN_LOW);
           #endif
           }
           else
           {
            // make turn on
            makeButtonOn(buttonPointer, pal);
           #ifdef __linux__
           gpioWrite(HOT_BUBL1, PIN_HIGH);
           gpioWrite(HOT_BUBL2, PIN_HIGH);
           gpioWrite(HOT_BUBL3, PIN_HIGH);

#endif
        }

    }
    else if(button_name == PDLC)
    {
        isOn_PDLC = !isOn_PDLC;

        buttonPointer = ui->pushButton_PDLC;
        pal = buttonPointer->palette();

        if(isOn_PDLC)
        {
            // make turn off
            makeButtonOff(buttonPointer, pal);
#ifdef __linux__
            gpioWrite(PDLC_PIN, PIN_LOW);
#endif
        }
        else
        {
            // make turn on
            makeButtonOn(buttonPointer, pal);
#ifdef __linux__
            gpioWrite(PDLC_PIN, PIN_HIGH);
#endif
        }

    }
    else if(button_name == WATER_PUMP)
    {
        isOn_waterPump = !isOn_waterPump;
        buttonPointer = ui->pushButton_waterPump;
        pal = buttonPointer->palette();

        if(isOn_waterPump)
        {
            // make turn off
            makeButtonOff(buttonPointer, pal);
#ifdef __linux__
            currentWaterPower = 0;
            gpioPWM(WATER_PUMP_PWM, currentWaterPower);
            ui->horizontalSlider_waterPumpSlider->setValue(currentWaterPower);
#endif
        }
        else
        {
            // make turn on
            makeButtonOn(buttonPointer, pal);
#ifdef __linux__
            currentWaterPower = 100;
            gpioPWM(WATER_PUMP_PWM, currentWaterPower);
            ui->horizontalSlider_waterPumpSlider->setValue(currentWaterPower);
#endif
        }

    }
    else if(button_name == DOOR_MOTOR)
    {
        isOn_doorMotor = !isOn_doorMotor;
        buttonPointer = ui->pushButton_doorMotor;
        pal = buttonPointer->palette();

        if(isOn_doorMotor)
        {
            // make turn off
            makeButtonOff(buttonPointer, pal);
#ifdef __linux__
            currentDoorPower = 0;
            gpioPWM(DOORLOC_MOTOR_PWM, currentDoorPower);
            ui->horizontalSlider_doorLock->setValue(currentDoorPower);
#endif
        }
        else
        {
            // make turn on
            makeButtonOn(buttonPointer, pal);
#ifdef __linux__
            currentDoorPower = 100;
            gpioPWM(DOORLOC_MOTOR_PWM, currentWaterPower);
            ui->horizontalSlider_doorLock->setValue(currentWaterPower);
#endif
        }

    }

    buttonPointer->setAutoFillBackground(true);
   // buttonPointer->update();

    return 0;
}

void ControlPanel::OnTimerCallbackFunc_CheckDoorOpen() // 문 열림 감지
{
    int isOn = -1;
#ifdef __linux__
    isOn = gpioRead(DOORLOC_CHECK_OPEN_SW);

    QLabel *doorLock_OpenSW = ui->doorLock_OpenSW;
    doorLock_OpenSW->setAutoFillBackground(true);
    QPalette pal = doorLock_OpenSW->palette();

    if(isOn)
    {
         // 문 완전히 개방됨
        pal.setColor(QPalette::Window, QColor(181, 217, 232));
        if(!isIgnoreOpenSW_Status) // Stop Door Lock Motor
        {
            currentDoorPower = 0;
            gpioPWM(DOORLOC_MOTOR_PWM, currentDoorPower);
            ui->horizontalSlider_doorLock->setValue(currentDoorPower);
        }
    }
    else
    {
        pal.setColor(QPalette::Window, QColor(Qt::transparent));
    }
    doorLock_OpenSW->setPalette(pal);
#endif
}
void ControlPanel::OnTimerCallbackFunc_CheckDoorClose() // 문 페쇄 감지
{
    int isOn = -1;
#ifdef __linux__
    isOn = gpioRead(DOORLOC_CHECK_CLOSE_SW);

    QLabel *doorLock_CloseSW = ui->doorLock_closeSW;
    doorLock_CloseSW->setAutoFillBackground(true);
    QPalette pal = doorLock_CloseSW->palette();

    if(isOn)
    {
        // 문 완전히 닫힘
       pal.setColor(QPalette::Window, QColor(181, 217, 232));
       if(!isIgnoreCloseSW_Status) // Stop Door Lock Motor
       {
           currentDoorPower = 0;
           gpioPWM(DOORLOC_MOTOR_PWM, currentDoorPower);
           ui->horizontalSlider_doorLock->setValue(currentDoorPower);
       }
    }
    else
    {
        pal.setColor(QPalette::Window, QColor(Qt::transparent));
    }
    doorLock_CloseSW->setPalette(pal);
#endif
}



void ControlPanel::on_radioButton_clicked() // 물펌프 순방향
{
#ifdef __linux__
            gpioWrite(WATER_PUMP_FB_SIGNAL, MOTOR_FORWARD);
#endif
}

void ControlPanel::on_radioButton_2_clicked() // 물펌프 역방향
{
#ifdef __linux__
            gpioWrite(WATER_PUMP_FB_SIGNAL, MOTOR_BACKWARD);
#endif
}

void ControlPanel::on_radioButton_3_clicked() // 도어락 모터 순방향
{
#ifdef __linux__
            gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_FORWARD);
#endif
}

void ControlPanel::on_radioButton_4_clicked() // 도어락 모터 역방향
{
#ifdef __linux__
            gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_BACKWARD);
#endif
}

void ControlPanel::on_checkBox_stateChanged(int arg1) // 물펌프
{
    qDebug() << arg1;
    if(arg1)
    {
        isIgnoreCloseSW_Status = true;
        isIgnoreOpenSW_Status = false;

    }
    else
    {
        isIgnoreCloseSW_Status = false;
        isIgnoreOpenSW_Status = true;
    }
}
