#include "Tool.h"

#include "Poco/JSON/Parser.h"
#include "unistd.h"
#include "sys/stat.h"
#include "fcntl.h"

using std::string;
using Poco::JSON::Object;
using Poco::JSON::Parser;

const char *Tool::db_pipe_name = "DBPIPE";
const char *Tool::sd_pipe_name = "SENDPIPE";

string Tool::jsonToStr(Object obj){
    Poco::Dynamic::Var var(obj);
    return var.toString();
}

Object Tool::strToJson(string str){
    Parser parser;
    Poco::Dynamic::Var var = parser.parse(str);
    Object obj = *var.extract<Poco::JSON::Object::Ptr>();
    return obj;
}

bool Tool::createFifo(){
    unlink(db_pipe_name);
    int res1 = mkfifo(db_pipe_name, 0777);
    if(res1 < 0){
        Tool::showMsgOnMainWindow("Create Pipe " + string(db_pipe_name) + " failed\n");
        return false;
    }
    unlink(sd_pipe_name);
    int res2 = mkfifo(sd_pipe_name, 0777);
    if(res2 < 0){
        Tool::showMsgOnMainWindow("Create Pipe " + string(sd_pipe_name) + " failed\n");
        return false;
    }
    return true;
}

string Tool::fifoRead(const char *pipe_name){
    int read_fd = open(pipe_name, O_WRONLY);
    if(read_fd == -1){
        Tool::showMsgOnMainWindow("Open Fifo "+string(pipe_name)+" Failed\n");
        return "";
    }
    char recvbuf[1024*1024];
    int len = read(read_fd, recvbuf, sizeof(recvbuf));
    if(len > 0){
        string return_msg = recvbuf;
        return return_msg;
    }
    else {
        return "";
    }

}

bool Tool::fifoWrite(const char *pipe_name, string msg){
    int write_fd = open(pipe_name, O_RDONLY);
    if(write_fd == -1){
        Tool::showMsgOnMainWindow("Write Fifo "+string(pipe_name)+" Failed\n");
        return false;
    }
    int len = write(write_fd, msg.c_str(), msg.length());
    if(len > 0){
        return true;
    }
    else
        return false;
}




