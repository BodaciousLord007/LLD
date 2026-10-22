#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex m;

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        lock_guard<mutex> lock(m);
        ++counter; // critical section
    }
}

int main()
{
    thread t1(increment), t2(increment);
    t1.join();
    t2.join();
    cout << "Final: " << counter << "\n"; // == 2000
}