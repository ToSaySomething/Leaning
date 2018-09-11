#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include <iostream>


class ThreadRunnable1 : public Poco::Runnable
{
public:
    int x = 0;
    ThreadRunnable1(){}
    ~ThreadRunnable1(){}
    void run();

};
void ThreadRunnable1::run(){
       while(1)
       {
           Poco::Thread thread1;
           thread1.sleep(1000);
           std::cout << "Hello,world!" << std::endl;
       }

}

class ThreadRunnable2 : public Poco::Runnable
{
     void run()
    {
        while(1)
        {
            Poco::Thread thread2;
            thread2.sleep(1000);
            std::cout << "*****Hello,world2!" << std::endl;
        }
    }
};

int main(int argc, char *argv[])
{
//    int vis[1024] = {0};
    ThreadRunnable1 run1;
    ThreadRunnable2 run2;
    Poco::ThreadPool pool1(2,3,3);
    std::cout <<"allocated:"<< pool1.allocated()<< std::endl;
    std::cout <<"used:"<< pool1.used()<< std::endl;
    int id = 3;
    while(id--){
        pool1.addCapacity(1);

        std::cout << " run1:id: " << id << std::endl;
        pool1.start(run1);
        std::cout <<"allocated:"<< pool1.allocated()<< std::endl;
        std::cout <<"used:"<< pool1.used()<< std::endl;
    }
   // pool1.addCapacity(1);
//    Poco::PooledThread xx;
//    std::cout << pool1.getStackSize()<< std::endl;

   // pool1.start(run1);
//    pool1.start(run1);
//    std::cout << pool1.getStackSize()<< std::endl;
   // pool1.start(run2);
      //  std::cout <<"allocated:"<< pool1.allocated()<< std::endl;
      //  std::cout <<"used:"<< pool1.used()<< std::endl;
//    Poco::Thread thread;
//    ThreadRunnable runnable[1024];
//    for(int i=0; i<10; i++)
//    {
//        std::cout << "ID:" << i << ": ";
//        thread.start(runnable[i]);
//        Poco::Thread::sleep(1000);
//        vis[i] = 1;
//        thread.join();
//    }
//    thread.join(l);
    return 0;
}
