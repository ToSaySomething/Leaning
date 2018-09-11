#ifndef TCPSERVER_H
#define TCPSERVER_H

class TCPConnection
{
public:
   /* TCPConnection(const StreamSocket& s):
        TCPServerConnection(s)
    {
    }
    void run();*/
    int isflag();
};


extern "C"
{
    TCPConnection ob;
    int isflag()
    {
        return ob.isflag();
    }
}

#endif // TCPSERVER_H
