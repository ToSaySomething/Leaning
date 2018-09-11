#include"head.h"

int main()
{
    char recvbuf[MAX_MSG_LEN];
    char sendbuf[MAX_MSG_LEN];
    int wfd, rfd;
    if(access(FIFO_READ, F_OK) == -1)
    {
        int res = mkfifo(FIFO_READ, 0666);
        if(res == -1)
        {
            perror("mkfifo READ");
            exit(EXIT_FAILURE);
        }
    }
    //server的写对应client读
    rfd = open(FIFO_WRITE, O_RDONLY);
    if(rfd == -1)
    {
        perror("open READ");
        exit(EXIT_FAILURE);
    }
    wfd = open(FIFO_READ, O_WRONLY);
    if(wfd == -1)
    {
        perror("open WRITE");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid == 0)//子进程用于写
    {
        while(1)
        {
            printf("Cli:>");
            scanf("%s", sendbuf);
            write(wfd, sendbuf, strlen(sendbuf)+1);
            if(strcmp(sendbuf, "quit") == 0)
                exit(EXIT_FAILURE);
        }
    }
    else if(pid > 0)
    {
        pid_t pid1 = fork();
        if(pid1 == 0)
        {
            while(1)
            {
                read(rfd, recvbuf, MAX_MSG_LEN);
                printf("Ser:>%s\n", recvbuf);
            }
        }
        else if(pid > 0)
        {
            int stat;
            wait(&stat);
            wait(&stat);
        }
    }
    return 0;
}
