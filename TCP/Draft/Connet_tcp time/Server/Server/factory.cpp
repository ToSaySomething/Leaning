#include "factory.h"

ServerConnection* MyConnectionFactory::createConnection(const StreamSocket& socket)
{
    return new Connection(socket);
}
