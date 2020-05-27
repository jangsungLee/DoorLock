#include "mainwindow.h"
#include "form.h"
#include "doorlocksystem.h"


#include <QDebug>
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>


#include <QNetworkAccessManager>
#include <QWidget>

// Main 소스코드에서 관리할 UI(여기서는 Widget을 사용하였음)들을 Pointer로 전달하면 MainWindow클래스에는 관리할 윈도우(Widget)을 자유롭게 만질수 있음
// 단, 주의사항은 Main에서 모두 다 생성을 해야함.
// Main이 아닌 곳에서 인스턴스를 생성하면 제대로 동작하지 않음.

// Socket *.pro => QT Modules += WebSocket NetWork



#include "websocket.h"

#define BUF_SIZE 1024
void ErrorHandling(const char* message);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form f;
    MainWindow w(nullptr, &f); // MainWindow에서 Form(f)를 접근(제어)하기 위해 포인터 전달.
    QWidget *windows[]={&w, &f};
    DoorLockSystem security(windows);

    f.addMainWindow(&w);// Form(f)에서 MainWindow를 접근(제어)하기 위해 포인터 전달.


    w.show();
    //f.show();
    security.show();

    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
    QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    WebSocket client(QUrl(QStringLiteral("ws://220.69.244.118:9000")), debug);
    //QObject::connect(&client, &WebSocket::closed, &a, &QCoreApplication::quit);
    w.websocket = &client;

    return a.exec();
}


void ErrorHandling(const char* message)
{
    qDebug() << message;
    qDebug() << '\n';
    exit(1);
}
