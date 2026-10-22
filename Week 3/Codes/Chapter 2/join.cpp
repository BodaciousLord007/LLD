#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

/*
A std::thread object's joinable() can change from false to true when 
you assign it ownership of a new thread using move assignment. 
*/
void work()
{
    cout << "[worker] using thread ID: " << std::this_thread::get_id() << "\n";
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "[worker] done\n";
}

int main(){
    cout << "Main Started\n";
    thread t(work);
    cout <<  "Is it Joinable before join?:" << boolalpha << t.joinable() << "\n";
    t.join();
    cout << boolalpha << "Is it Joinable after join?:" << boolalpha << t.joinable() << "\n";
    cout << "Main Finished\n";
    return 0;
}