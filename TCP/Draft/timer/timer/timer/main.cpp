#include "timer.h"
#include <stdio.h>


int main()
{
    std::cout << "Hello World!" << std::endl ;

    StatTimer *timer = new StatTimer();
    if (!timer->start())
    {
        std::cout << "Failed to start timer" << std::endl;;
    }

    while (true)
    {
        timer->set(0);
        if (timer->end)
        {
            timer->stop();
            break;
        }
    }

    std::cout << std::endl;
    return 0;
}
