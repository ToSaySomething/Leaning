#include "msgqueue.h"

int main(int argc, char *argv[])
{
    IpcMsg Msg;
    key_t key;
    key = 0x00001010;
    //Msg.m_key = key;
    if(!Msg.isExist(key))
    {
        //Msg.m_msgid = Msg.create(key);


    }
    return 0;
}
