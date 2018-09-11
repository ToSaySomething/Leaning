#ifndef CUSTOM_THREAD_H
#define CUSTOM_THREAD_H

#include <pthread.h>

// 自定义线程类
class CustomThread
{
public:
	//void ~CustomThread() {}
	// 启动线程
    int start();
	// 等待线程退出
    void* join();
	
    int detach();
	
    int equals(CustomThread* t);
	
    void exit(void* value_ptr);
	
    int cancel();

    pthread_t getThread();
	
protected:
    virtual void run() = 0;

private:
    static void* go(void* obj);
    pthread_t m_thread;
};

#endif // CUSTOM_THREAD_H
