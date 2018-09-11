#ifndef CUSTOM_THREAD_H
#define CUSTOM_THREAD_H

#include <pthread.h>

class CustomThread
{
public:
    int start();
	
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
