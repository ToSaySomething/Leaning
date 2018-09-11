#include "msgqueue.h"
//消息队列创建方法定义
int IpcMsg::create(int key)
{
    int msgid;											//定义描述符变量
    if ((msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600)) == -1) //调用创建消息队列方法进行判断
    {
        std::cout<<"创建消息队列错误"<<std::endl;					//如果创建失败，打印提示信息
    }
    return msgid;										//返回相应的消息队列描述符
}
//删除消息队列方法定义
void IpcMsg::remove(int key)
{
    int msgid;											//定义描述符变量
    if ((msgid = msgget(key, 0)) != -1) 						//调用打开或创建消息队列方法进行判断
    {
        msgctl(msgid, IPC_RMID, (struct msqid_ds*)0);		//如果存在则删除
    }
}
//判断消息队列是否存在方法定义
int IpcMsg::isExist(int key)
{
    int msgid;											//定义描述符变量
    if ((msgid = msgget(key, IPC_CREAT | IPC_EXCL)) == -1) 	//调用打开或创建消息队列方法进行判断
    {
        return 1;										//如果存在则返回1
    }
    msgctl(msgid, IPC_RMID, (struct msqid_ds*)0);			//否则删除创建的消息队列
    return 0;
}
//获取消息队列key方法定义
long IpcMsg::getkey()
{
    return m_key;										//返回相应的消息队列key值
}
//获取消息队列描述符方法定义
long IpcMsg::getipcid()
{
    return m_msgid;									//返回相应消息队列的描述符
}
//获取消息队列消息数方法定义
long IpcMsg::getmsgcnt()
{
    struct msqid_ds _mds;								//定义消息队列状态结构对象
    if (msgctl(m_msgid, IPC_STAT, &_mds) == -1) 			//调用相应控制方法获取状态信息
    {
        std::cout<<"获取状态失败!"<<std::endl;
    }
    return _mds.msg_qnum;								//返回相应的消息数成员值
}
//获取消息队列当前字节数方法定义
long IpcMsg::getcbytes()
{
    struct msqid_ds _mds;								//定义消息队列状态结构对象
    if (msgctl(m_msgid, IPC_STAT, &_mds) == -1) 			//调用相应控制方法获取状态信息
    {
        std::cout<<"获取状态失败!"<<std::endl;
    }
    return _mds.msg_cbytes;								//返回相应的消息队列字节数
}
//获取消息队列中最大容量字节数方法定义
long IpcMsg::getqbytes()
{
    struct msqid_ds _mds;								//定义消息队列状态结构对象
    if (msgctl(m_msgid, IPC_STAT, &_mds) == -1) 			//调用相应控制方法获取状态信息
    {
        std::cout<<"获取状态失败!"<<std::endl;
    }
    return _mds.msg_qbytes;								//返回相应的消息队列最大容量
}
//发送消息方法定义
int IpcMsg::put(IpcMsgBuf& msg, int msglen, int flag=0)
{
    if (msgsnd(m_msgid, &msg, msglen, 0|flag) == -1) 			//调用发送数据并判断返回值
    {
        if (errno == EAGAIN)
        {
            return -1;
        }
        else
        {
            std::cout<<"发送消息错误"<<std::endl;
        }
    }
    return 0;
}
//接受消息方法定义
int IpcMsg::get(IpcMsgBuf& msg, int msglen, int flag=0)
{
    if (msgrcv(m_msgid, &msg, msglen, 0, 0|flag) == -1) 		//调用接受消息数据方法判断返回值
    {
        if (errno == ENOMSG)
        {
            return -1;
        }
        else
        {
            std::cout<<"接收消息错误"<<std::endl;
        }
    }
    return 0;
}
