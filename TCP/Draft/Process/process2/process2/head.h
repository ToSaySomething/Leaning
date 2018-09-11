#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define FIFO_READ "readfifo"
#define FIFO_WRITE "writefifo"
#define MAX_MSG_LEN 256

void handler (int signum)
{
    unlink(FIFO_READ);
    unlink(FIFO_WRITE);
    exit(1);
}

#endif // HEAD_H
