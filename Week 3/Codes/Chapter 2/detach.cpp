#include<iostream>
#include<thread>
#include<chrono>
#include<random>

using namespace std;

int main(){
    thread t([](){
        cout << "Background task started\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Background Task Finished\n";
    });

    t.detach();
    
    // Thread Ditach so mains goes on as expected
    srand(time(0));
    int exitTime = rand() % 200;
    
    cout << "Main Exiting in " << exitTime << "\n";
    
    this_thread::sleep_for(chrono::milliseconds(exitTime));
    
    cout << "Main Exiting" << "\n";
    return 0;
}