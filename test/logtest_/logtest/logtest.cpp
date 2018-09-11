#include "logtest.h"

class Thread1: public CustomThread
{
public:
    Thread1(int _type):type(_type){}
    ~Thread1(){}
protected:
    void run();
    int type;
};

void Thread1::run()
{
    void* hLog1 = cwLogCreateInstance();
    cwLogOpenFile(hLog1, "./LogOutput/log1.txt");
    int t = 100;
    while(t--){
        switch(type){
            case 1: cwLogWrite(hLog1, LOGLEVEL_INFO, "this is a information.");break;
            case 2: cwLogWrite(hLog1, LOGLEVEL_WARN, "this is a warning.");break;
            case 3: cwLogWrite(hLog1, LOGLEVEL_DEBUG, "this is a debug.");break;
            case 4: cwLogWrite(hLog1, LOGLEVEL_FATAL, "this is a fatal.");break;
            case 5: cwLogWrite(hLog1, LOGLEVEL_ERROR, "this is a error.");break;
        }
    }
    sleep(50);
    cwLogCloseFile(hLog1);
	cwLogDestroyInstance(hLog1);
}


int main()
{
    while(1){
        Thread1 t1(1);
        Thread1 t2(2);
        Thread1 t3(3);
        Thread1 t4(4);
        Thread1 t5(5);
        t1.start();  
        t2.start();
        t3.start();
        t4.start();
        t5.start();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
    }
    
    return 0;
}