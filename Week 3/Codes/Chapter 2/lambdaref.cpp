#include<iostream>
#include<thread>
using namespace std;
int main(){
    int x = 5;
    // Capture by Reference
    // thread t1([&](){
    //     x++;
    // });
    // t1.join();



    // Capture by Value
    thread t2([=](){
        // x += 5; --> As x is readonly value
        cout << x + 5 << endl;
    });
    t2.join();

    cout << x << "\n";
    return 0;
}