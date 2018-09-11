
//消息队列客户端chapter2402_02.cpp

#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

const int BUFFER = 512;

//消息结构体定义
struct msgdata
{
     long mtype;  //消息类型
     char buffer[BUFFER+1];  //消息数据缓冲区
};

//打开或创建消息队列方法定义
int create(int key)
{
         int msgid;  //定义消息队列描述符
         if((msgid = msgget(key, 0666|IPC_CREAT)) == -1)//调用打开或创建方法并判断返回值
         {
                   std::cout<<"create msg queue fail!"<<std::endl;
         }
         return msgid; //返回相应的消息队列描述符
}

//发送消息方法定义
int put(int msgid,msgdata& msg, int msglen, int flag)
{
         if(msgsnd(msgid, &msg, msglen, 0|flag) == -1)  //调用发送消息方法，判断返回值
         {
                   if(errno == EAGAIN)
                   {
                            return -1;
                   }
                   else
                   {
                            std::cout<<"send msg fail!"<<std::endl;
                   }

         }
         return 0;

}

//获取消息方法定义
int get(int msgid,msgdata& msg, int msglen, int flag)
{
         if(msgrcv(msgid, &msg, msglen, 0, 0) == -1)  //调用接受消息方法，判断返回值
         {
                   if(errno == ENOMSG)   //如果请求的类型消息不存在
                   {
                            return -1;
                   }
                   else
                   {
                            std::cout<<"recv msg fail!"<<std::endl;
                   }
         }
         return 0;

}


//put
int main(int argc,char *argv[])
{

    struct msgdata msg;    //定义消息结构体对象
    key_t key;  //定义相应key值变量
    int msgid = -1;   //定义消息队列描述符变量
    key = (key_t)1234;   //初始化相应的key值
    char buff[BUFFER];

    msgid = create(key);   //调用打开或创建方法打开指定消息队列

    std::cout << msgid << std::endl;

    bool flag = true;
    while(flag)
    {
        fgets(buff, BUFFER, stdin);

        msg.mtype = 2;      //设定消息类型
        strcpy(msg.buffer,buff);  //将参数项数据拷贝至消息对象缓冲区
        put(msgid,msg,BUFFER,0);    //发送消息数据


        if(strncmp(buff, "end", 3) == 0 )
            flag = false;
        memset(&msg,0,BUFFER);   //清空并初始化消息对象
        // get(msgid,msg,BUFFER,0);    //接受消息数据
        std::cout<<"Client send:"<<msg.buffer<<std::endl;    //打印接受到的消息数据
        sleep(1);
    }
    puts("exit success");
    exit(EXIT_SUCCESS);
    return 0;
}
