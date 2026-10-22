#include<iostream>
#include<thread>

using namespace std;
void hello(string name){
    cout << "Hello " << name << "\n";
}

int main(){
    thread t(hello, "Anurag");
    t.join();
    cout << "Main finished\n";
    return 0;
}