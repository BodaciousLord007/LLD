#include<iostream>
#include<chrono>
#include<thread>
using namespace std;

int cnt = 0; // Not Protected or Atomic

void task(int increase){
    for(int i = 0; i < increase; i++)cnt += 1;
}
int main(){
    int x = 100000;
    int y = 100000;
    thread t1(task, x);
    thread t2(task, y);
    t1.join();
    
    t2.join();
    cout << "Expected:" << x + y << "\n";
    cout << "Reality:" << cnt << "\n";

    return 0;
}