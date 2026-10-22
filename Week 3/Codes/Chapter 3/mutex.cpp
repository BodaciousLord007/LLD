#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int counter = 0;
mutex m;

void increment()
{
    for (int i = 0; i < 100000; ++i)
    {
        m.lock();
        ++counter;
        m.unlock();
    }
}

int main()
{
    thread t1(increment), t2(increment);
    t1.join();
    t2.join();
    cout << "Final: " << counter << "\n"; // often < 2000
}