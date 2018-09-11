
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/SocketAddress.h"
#include "activity.h"
using Poco::Net::StreamSocket;

int main(int argc, char *argv[])
{
    Poco::Net::ServerSocket so ( 9000 );

    MyActivity example(so);//a thread
    example.start();
    std::cout << "w22 running." << std::endl;
    Thread::sleep(200000);
    example.stop();

    return 0;
}



