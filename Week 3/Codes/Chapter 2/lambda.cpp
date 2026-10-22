#include<iostream>
#include<thread>

using namespace std;

int main(){
    int x = 5;
    cout << "Main Starting\n";
    // Copy Capture
    thread t1([x](){
        cout << "Thread Starting\n";
        int y = x + 5;
        cout << "Y->" << y << "\n";
        cout << "Thread Ending\n";
    });

    t1.join();
    cout << "Main Exiting\n" << endl;
    return 0;
}