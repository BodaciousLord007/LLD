#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void task(string name){
    for(int i = 0; i < 3; i++){
        cout << name << " says hello " << i << std::endl;
        this_thread::sleep_for(chrono::microseconds(10));
    }
}
int main(){
    thread t1(task, "Person 1");
    thread t2(task, "Person 2");

    t1.join();
    t2.join();
    return 0;
}