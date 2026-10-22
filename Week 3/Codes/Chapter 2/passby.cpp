#include<iostream>
#include<thread>
using namespace std;

void increment(int &x){
    x++;
    return;
}

int main(){
    int x = 0;
    thread t(increment, ref(x));
    t.join();
    cout << x << endl;
    return 0;
}