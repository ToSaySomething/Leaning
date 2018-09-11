#include "serverconnect.h"

ServerConnection::ServerConnection(const StreamSocket& socket):
    _socket(socket)
{
}


ServerConnection::~ServerConnection()
{
}


void ServerConnection::start()
{
    try
    {
        run();
    }
    catch (Exception& exc)
    {
        ErrorHandler::handle(exc);
    }
    catch (std::exception& exc)
    {
        ErrorHandler::handle(exc);
    }
    catch (...)
    {
        ErrorHandler::handle();
    }
}

