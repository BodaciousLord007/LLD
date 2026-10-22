#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
using namespace std;

std::mutex m1, m2;

// Issue
/*
void f()
{
    lock_guard<std::mutex> g1(m1);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<std::mutex> g2(m2);
    cout << "f done\n";
}

void g()
{
    lock_guard<std::mutex> g1(m2);
    this_thread::sleep_for(std::chrono::milliseconds(10));
    lock_guard<std::mutex> g2(m1);
    std::cout << "g done\n";
}
*/

// Fix -> Just m1->m2 for both istead of one holding m1->m2 and other m2->m1
void f()
{
    lock_guard<std::mutex> g1(m1);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<std::mutex> g2(m2);
    cout << "f done\n";
}

void g()
{
    lock_guard<std::mutex> g1(m1);
    this_thread::sleep_for(std::chrono::milliseconds(10));
    lock_guard<std::mutex> g2(m2);
    std::cout << "g done\n";
}
int main()
{
    std::thread t1(f), t2(g);
    t1.join();
    t2.join();
    return 0;
}