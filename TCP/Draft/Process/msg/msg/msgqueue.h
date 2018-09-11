#ifndef MSGQUEUE_H
#define MSGQUEUE_H

//消息队列操作类封装头文件
#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

#define BUFFER_SIZE 512
//消息结构体
struct IpcMsgBuf
{
    long m_type;										//消息类型
    char m_text[BUFFER_SIZE+1];							//消息数据
};
//消息队列操作类
class IpcMsg
{
public:
    IpcMsg(){}										//消息队列操作类构造函数
    ~IpcMsg(){}									//消息队列操作类析构函数

    int create(int key);								//消息队列创建方法
    void remove(int key);								//消息队列删除方法
    int isExist(int key);								//判断指定消息队列是否存在方法
    long getkey();									//获取消息队列key值方法
    long getipcid();									//获取消息队列描述符方法
    long getmsgcnt();								//获取消息队列消息数方法
    long getcbytes();								//获取消息队列当前字节数方法
    long getqbytes();								//获取消息队列中最大容量字节数方法
    int put(IpcMsgBuf& msg, int msglen, int flag);			//发送消息方法
    int get(IpcMsgBuf& msg, int maxmsglen, int flag);		//获取消息方法
private:
        int m_key;										//消息队列key值
        int m_msgid;									//消息队列描述符
};

//消息队列操作类封装源文件


#endif // MSGQUEUE_H
