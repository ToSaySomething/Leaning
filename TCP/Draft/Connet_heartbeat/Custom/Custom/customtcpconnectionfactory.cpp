#include "customtcpconnectionfactory.h"

TCPServerConnection* CustomTCPConnectionFactory::createConnection(const StreamSocket& socket)
{
    return new CustomTCPConnection(socket);
}
