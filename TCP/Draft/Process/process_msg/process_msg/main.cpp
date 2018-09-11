
//消息队列服务端chapter2402_01.cpp

#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
const int BUFFER = 512;

//消息队列结构体
struct msgdata
{
     long mtype;  //消息类型
     char buffer[BUFFER+1];  //消息数据缓冲区
};

//创建消息队列
int create(int key)
{
     int msgid;  //定义相应的消息队列描述符变量
     if((msgid = msgget(key, IPC_CREAT |  0666)) == -1)     //调用创建消息队列方法，返回描述符??
     {
         std::cout<<"createmsg queue fail!"<<std::endl;   //如果创建不成功则提示
     }
     return msgid;   //返回相应的消息队列描述符
}

//发送消息
int put(int msgid, msgdata& msg, int msglen, int flag)
{
    if(msgsnd(msgid, &msg, msglen, 0|flag) == -1) //调用消息发送方法，并作判断
    {
        if(errno == EAGAIN)  //消息不能被发送直接返回-1
        {
            return -1;
        }
        else
        {
            std::cout<<"sendmsg fail!"<<std::endl;
        }
    }
         return 0;
}

//接受消息
int get(int msgid,msgdata& msg, int msglen, int flag)
{
     if(msgrcv(msgid, &msg, msglen, 2, 0|flag) == -1)  //调用接受消息方法进行判断
     {
         if(errno == ENOMSG)   //如果请求的类型消息不存在
         {
             return -1;
         }
         else
         {
             std::cout<<"recvmsg fail!"<<std::endl;
         }

     }
      std::cout<<msg.buffer<<std::endl;
     return 0;
}

//删除消息队列方法定义
void remove(int key)
{
    int msgid;											//定义描述符变量
    if ((msgid = msgget(key, 0)) != -1) 						//调用打开或创建消息队列方法进行判断
    {
        msgctl(msgid, IPC_RMID, (struct msqid_ds*)0);		//如果存在则删除
    }
}

int main()
{
    struct msgdata msg;  //定义消息结构体对象
    key_t key;  //定义对应的key值变量
    int msgid = -1;  //定义相应消息队列描述符变量
    key = (key_t)1234;  //初始化消息队列key值
    msgid = create(key); //调用创建消息队列方法

    std::cout << msgid << std::endl;

    long int msgtype = 2;

    bool flag = true;
    while(flag)
    {
        sleep(1);
        memset(&msg,0,BUFFER);
        int ret = get(msgid, msg, BUFFER, 0);    //循环体中调用get方法接受消息

        printf("msg type = %ld\n", msg.mtype);
        printf("msg content = %s"
               "\n", msg.buffer);
        if(strncmp(msg.buffer, "end", 3) == 0 )
            flag = false;
    }
    remove(key);
    exit(EXIT_SUCCESS);
    return 0;
}
