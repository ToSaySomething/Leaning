
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <string.h>

#define _PATH_ "./yfifo"
const int _SIZE = 100;

void do1()
{
    printf("---do1---\n");
    int ret = mkfifo(_PATH_,0600|S_IFIFO);
    if(ret == -1)
    {
        perror("create error\n");
        return;
    }
    int fd = open(_PATH_, O_WRONLY);
    if(fd < 0)
    {
        printf("open error\n");
        return ;
    }
    char buff[_SIZE];
    memset(buff, '\0', sizeof(buff));

    while(true)
    {
        read(0, buff, sizeof(buff));
        int ret = write(fd,buff,strlen(buff)-1);
        printf("----write\n");
        buff[ret] = '\0';
        if( ret < 0 )
        {
            printf("write error!\n");
            break;
        }
        if(strncmp(buff, "end", 3)==0)
        {
            break;
        }
    }
    close(fd);
}


void do2()
{
    printf("---do2---\n");

    int fd = open(_PATH_,O_RDONLY);
    if(fd<0)
    {
        printf("open file error!\n");
        return ;
    }
    char buf[_SIZE];
    memset(buf,'\0',sizeof(buf));
    while(1)
    {
        int ret = read(fd,buf,sizeof(buf));
        if(ret <= 0)
        {
            printf("read end or error!\n");
            break;
        }
        printf("---read: %s\n",buf);
        if(strncmp(buf,"quit",4) == 0)
        {
            break;
        }
    }
    close(fd);
}

int main()
{

    //net -> sql
    pid_t child = fork();

    int fd[2];// sql read; tcp write
    if(child)
    {//parent
        printf("------in parent-----: parantpid=%d\n",(int)getpid());
        printf("------in parent-----: childpid=%d\n\n",child);
        do1();
    }
    else
    {
        printf("------in child-----: pid=%d\n",(int)getpid());
        printf("------in child-----: parent pid=%d\n\n",getppid());
        do2();
    }
    unlink(_PATH_);//删除管道文件
    return 0;
}


/*
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"

#include <fstream>
using Poco::Process;
using Poco::ProcessHandle;

int main(int argc, char** argv)
{
    std::string cmd("/bin/ps");
    std::vector<std::string> args;
    args.push_back("-re");
    Poco::Pipe outPipe;
    ProcessHandle ph = Process::launch("/bin/ps", args, 0, &outPipe, 0);//run
    Poco::PipeInputStream instr(outPipe);
    std::ofstream ostr("processes.txt");
    Poco::StreamCopier::copyStream(instr, ostr);

    /// After a Pipe has been passed as inPipe, only write operations are valid.
    /// After a Pipe has been passed as outPipe or errPipe,only read operations are valid.

     Poco::Pipe outPipe;
     Process::Args args;
     ProcessHandle ph(Process::launch("/bin/ps", args, 0, &outPipe, 0));
     Poco::PipeInputStream istr(outPipe);
//    ... // read output of ps from istr
     int rc = ph.wait();
//    Poco::Pipe in;

//    Poco::Pipe out;
//    ProcessHandle ph = Process::launch(cmd, args, &in, &out, 0);
//    Poco::PipeInputStream istr(outPipe);
//    std::ofstream ostr("processes.txt");
//    char buff[10] = "requst";

//    Poco::StreamCopier::copyStream(istr, ostr);



    return 0;
}
*/
