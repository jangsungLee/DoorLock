#include "mainwindow.h"
#include "form.h"
#include "doorlocksystem.h"

#include "websocketserver.h"

#include <QDebug>
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

// Main 소스코드에서 관리할 UI(여기서는 Widget을 사용하였음)들을 Pointer로 전달하면 MainWindow클래스에는 관리할 윈도우(Widget)을 자유롭게 만질수 있음
// 단, 주의사항은 Main에서 모두 다 생성을 해야함.
// Main이 아닌 곳에서 인스턴스를 생성하면 제대로 동작하지 않음.

// Socket *.pro => QT Modules += WebSocket NetWork

#include <QProcess>

#include "websocket.h"

#define BUF_SIZE 1024
void ErrorHandling(const char* message);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *windows[3];
    Form f(windows);
    MainWindow w(windows); // MainWindow에서 Form(f)를 접근(제어)하기 위해 포인터 전달.
    DoorLockSystem security(windows);
    windows[0]=&security;
    windows[1]=&w;
    windows[2]=&f;



    w.show();
    f.show();
    security.show();

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
