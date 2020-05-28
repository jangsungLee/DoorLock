#include "mainwindow.h"
#include "form.h"
#include "doorlocksystem.h"
#include "controlpanel.h"

#include "websocketserver.h"

#include <QDebug>
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

// Main 소스코드에서 관리할 UI(여기서는 Widget을 사용하였음)들을 Pointer로 전달하면 MainWindow클래스에는 관리할 윈도우(Widget)을 자유롭게 만질수 있음
// 단, 주의사항은 Main에서 모두 다 생성을 해야함.
// Main이 아닌 곳에서 인스턴스를 생성하면 제대로 동작하지 않음.

// Socket *.pro => QT Modules += WebSocket NetWork

#include <QMessageBox>
#include <QProcess>

#include "websocket.h"



#ifdef __linux__
#include <pigpio.h>
#endif

#define BUF_SIZE 1024
void ErrorHandling(const char* message);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *windows[3];
    Form f(windows);
    MainWindow w(windows); // MainWindow에서 Form(f)를 접근(제어)하기 위해 포인터 전달.
    DoorLockSystem security(windows);
    ControlPanel controlPanel(nullptr);

    windows[0]=&security;
    windows[1]=&w;
    windows[2]=&f;


#ifdef __linux__
    int __result = gpioInitialise();
    if (__result)
    {
       // pigpio initialisation failed.
        QMessageBox msgBox;
        msgBox.setText("pigpio initialisation failed.");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Retry | QMessageBox::Reset);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Reset:
           /* QStringList arguments;
            arguments<< "shutdown" << "-r" << "now";
            QProcess::execute(arguments);


            QString program = "shutdown";
            QStringList arguments;
            arguments << " -r" << " now";*/

            QProcess::execute("shutdown -r now");
            break;
        case QMessageBox::Retry:
            gpioInitialise();
            break;
        }
    }
    // pigpio initialised okay.

    // set Pin Mode
    gpioSetMode(BUBL1, PI_OUTPUT);
    gpioSetMode(BUBL2, PI_OUTPUT);
    gpioSetMode(BUBL3, PI_OUTPUT);
    gpioSetMode(BUBL4, PI_OUTPUT);
    gpioSetMode(BUBL5, PI_OUTPUT);
    gpioSetMode(BUBL6, PI_OUTPUT);
    gpioSetMode(BUBL7, PI_OUTPUT);
    gpioSetMode(BUBL8, PI_OUTPUT);


    gpioSetMode(HOT_BUBL1, PI_OUTPUT);
    gpioSetMode(HOT_BUBL2, PI_OUTPUT);
    gpioSetMode(HOT_BUBL3, PI_OUTPUT);

    gpioSetMode(PDLC_PIN, PI_OUTPUT);

    gpioSetMode(WATER_PUMP_FB_SIGNAL, PI_OUTPUT);
    gpioSetMode(WATER_PUMP_PWM, PI_OUTPUT);


    gpioSetMode(DOORLOC_MOTOR_FB_SIGNAL, PI_OUTPUT);
    gpioSetMode(DOORLOC_MOTOR_PWM, PI_OUTPUT);
    gpioSetMode(DOORLOC_CHECK_OPEN_SW, PI_INPUT);
    gpioSetMode(DOORLOC_CHECK_CLOSE_SW, PI_INPUT);

    // set Pin Power off
    gpioWrite(BUBL1, PIN_LOW);
    gpioWrite(BUBL2, PIN_LOW);
    gpioWrite(BUBL3, PIN_LOW);
    gpioWrite(BUBL4, PIN_LOW);
    gpioWrite(BUBL5, PIN_LOW);
    gpioWrite(BUBL6, PIN_LOW);
    gpioWrite(BUBL7, PIN_LOW);
    gpioWrite(BUBL8, PIN_LOW);


    gpioWrite(HOT_BUBL1, PIN_LOW);
    gpioWrite(HOT_BUBL2, PIN_LOW);
    gpioWrite(HOT_BUBL3, PIN_LOW);

    gpioWrite(PDLC_PIN, PIN_LOW);

    gpioWrite(WATER_PUMP_FB_SIGNAL, PIN_LOW);
    gpioWrite(WATER_PUMP_PWM, PIN_LOW);
    gpioSetPWMrange(WATER_PUMP_PWM, 100);


    gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, PIN_LOW);
    gpioWrite(DOORLOC_MOTOR_PWM, PIN_LOW);
    gpioSetPWMrange(DOORLOC_MOTOR_PWM, 100);
#endif


 //   w.show();
 //   f.show();
 //   security.show();
    controlPanel.show();

   /* QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
    QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    WebSocket client(QUrl(QStringLiteral("ws://220.69.244.118:9000")), debug);

    w.websocket = &client;*/

    bool debug = true;
    int port = 1234;

    WebSocketServer *server = new WebSocketServer(port, debug);
    QObject::connect(server, &WebSocketServer::closed, &a, &QCoreApplication::quit);



    return a.exec();
}


void ErrorHandling(const char* message)
{
    qDebug() << message;
    qDebug() << '\n';
    exit(1);
}
