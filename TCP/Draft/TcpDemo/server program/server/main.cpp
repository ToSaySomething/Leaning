#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/SocketAddress.h"

int main(int argc, char *argv[])
{
   Poco::Net::ServerSocket ses(5004);
   while(1)
   {
       Poco::Net::StreamSocket sts = ses.acceptConnection();
       Poco::Net::SocketStream sos(sts);
       sos<<"HTTP/1.0 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html><head><title>My 1st Web Server</title></head>"
            "<body><h1>Hello,Wordl!</h1></body></html>"
            "\r\n"
       << std::flush;
   }

    return 0;
}
