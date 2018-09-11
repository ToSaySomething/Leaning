#include "servermain.h"

int main(int argc, char *argv[])
{

    return CustomTCPServer().run(argc, argv);;
}



//    Params::Ptr params = new Params;
//    params->setMaxQueued( 10 );//设定队列的最大长度
//    params->setMaxThreads( 10 );//设定　TcpServer 最大线程的个数

//    ThreadPool threadpool(7,7,7);

//    Poco::Net::ServerSocket socket ( 9000 );
//    MyActivity server(socket, threadpool, params, new MyConnectionFactory());//a thread
//    server.start();
//    Thread::sleep(20000000);
//    server.stop();
