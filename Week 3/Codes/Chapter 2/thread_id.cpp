#include<iostream>
#include<thread>
#include<vector>
#include<chrono>

using namespace std;

int main(){
    cout << "Numbers of threads:" << thread::hardware_concurrency() << "\n";
    cout << "Main Thread ID:" << this_thread::get_id() << "\n";
    
    int N = 5;
    vector<thread> threads;
    threads.reserve(N);
    for(int i = 0; i < N; i++){
        threads.emplace_back([i](){
            this_thread::sleep_for(chrono::microseconds(100));
            cout << "Worker " << i + 1 << " ID:" << this_thread::get_id()<< "\n";  
        });
    }
    for(auto &t: threads)t.join();
    cout << "All Worker Joined\n";
    return 0;
}