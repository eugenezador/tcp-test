#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent)
    : QObject{parent}
{

}

void TcpSocket::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &TcpSocket::connected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpSocket::disconnected);
    connect(socket, &QTcpSocket::bytesWritten, this, &TcpSocket::bytesWritten);
    connect(socket, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("youtube.com", 80);

    // need to wait...
    if(!socket->waitForConnected(5000))
    {
            qDebug() << "Error: " << socket->errorString();
    }
}

void TcpSocket::connected()
{
    qDebug() << "connected...";

        // Hey server, tell me about you.
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void TcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void TcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";

}

void TcpSocket::readyRead()
{
    qDebug() << "reading...";

        // read the data from the socket
        qDebug() << socket->readAll();
}

