#include "customthread.h"

int CustomThread::start()
{
    if (pthread_create( &m_thread, 0, &CustomThread::go, this)) {
        return -1;
    }
    return 0;
}

void* CustomThread::go(void* obj)
{
    reinterpret_cast<CustomThread*>(obj)->run();
    return NULL;
}

void* CustomThread::join()
{
    void* ret;
    pthread_join(m_thread, &ret);
    return ret;
}

pthread_t CustomThread::getThread()
{
    return m_thread;
}

int CustomThread::detach()
{
    return pthread_detach(m_thread);
}

int CustomThread::equals(CustomThread* t)
{
    return pthread_equal(m_thread, t->getThread());
}

void CustomThread::exit(void* value_ptr)
{
    pthread_exit(value_ptr);
}

int CustomThread::cancel()
{
    return pthread_cancel(m_thread);
}

