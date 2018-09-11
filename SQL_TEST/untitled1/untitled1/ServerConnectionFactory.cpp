#include "ServerConnectionFactory.h"

TCPServerConnection* ServerConnectionFactory::createConnection(const StreamSocket &socket)
{
    return new ServerConnection(socket);
}
