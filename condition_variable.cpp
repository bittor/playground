#include <cstdio>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

mutex mtxA;
mutex mtxB;
condition_variable cv;
atomic_bool stat;
volatile int content = 0;

void threadA()
{
        while(1)
        {
        unique_lock<mutex> lk(mtxA);
        cv.wait(lk, []{return !stat.load();});
        printf("A see content:%d\n", content);
        this_thread::sleep_for(milliseconds(1));
        lk.unlock();
        }
}

void threadB()
{
        while(1)
        {
        unique_lock<mutex> lk(mtxB);
        cv.wait(lk, []{return !stat.load();});
        printf("B see content:%d\n", content);
        this_thread::sleep_for(milliseconds(1));
        lk.unlock();
        /* something */
        }
}

int main()
{
        stat.store(false);
        thread tA(threadA);
        thread tB(threadB);
        srand(time(nullptr));
        while(1)
        {
                unique_lock<mutex> lkA(mtxA, defer_lock);
                unique_lock<mutex> lkB(mtxB, defer_lock);
                int x;
                //cin >> x; 
                x = rand(); 
                stat.store(true);
                lock(lkA, lkB);
                content = x;
                stat.store(false);
                cv.notify_all();
                this_thread::sleep_for(milliseconds(1));
        }
        return 0;
}
