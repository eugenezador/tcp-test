#include <QCoreApplication>
#include "tcpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpSocket socket;
    socket.doConnect();

    return a.exec();
}
