#include "websocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

WebSocket::WebSocket(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocket::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocket::closed);
    m_webSocket.open(QUrl(url));
    m_url = url;
}

void WebSocket::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocket::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &WebSocket::onBinaryMessageReceived);

    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void WebSocket::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Text Message received:" << message;
    //m_webSocket.close();
}

void WebSocket::onBinaryMessageReceived(QByteArray message)
{
    //if (m_debug)
        qDebug() << "Binary Message received:" << message;
    //m_webSocket.close();

}

void WebSocket::closed()
{
    qDebug() << "Connection is closed, Retry Connection.";
    m_webSocket.open(QUrl(m_url));

}
