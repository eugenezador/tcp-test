#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent)
    : QObject{parent}
    , socket(new QTcpSocket(this))
{

    connect(socket, &QTcpSocket::connected, this, &TcpSocket::connected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpSocket::disconnected);
    connect(socket, &QTcpSocket::bytesWritten, this, &TcpSocket::bytesWritten);
    connect(socket, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("192.168.2.10", 800);

    // need to wait...
    if(!socket->waitForConnected(5000))
    {
            qDebug() << "Error: " << socket->errorString();
    }
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
    socket->connectToHost("192.168.2.10", 800);

    // need to wait...
    if(!socket->waitForConnected(5000))
    {
            qDebug() << "Error: " << socket->errorString();
    }
}

void TcpSocket::connected()
{
    qDebug() << "connected...";

    socket->write("");
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
    received_data.append(socket->readAll());


    qDebug() << "reading: ";
    // read the data from the socket
//    qDebug() << socket->readAll();

//    qDebug() << received_data.toUInt();

    for(int i = 0; i < received_data.size(); i++){
        tcp_data_array.append(received_data[i]);
//        qDebug() << received_data[i] << " : ";
    }

    for(int i = 0; i < tcp_data_array.size(); i++)
    qDebug() << tcp_data_array[i];
}

