#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<mutex>
using namespace std;

mutex m;
int shared = 0;
void work(int id){
    // Prep
    int local = 2 * id;

    //Lock
    unique_lock<mutex> lk(m,defer_lock); // Defer Lock -> Tells dont lock yet
    lk.lock();                           // enter critical section exactly when needed
    shared += local;
    std::cout << "T" << id << " added " << local << ", shared=" << shared << "\n";

    // Done with shared state: release early to shorten contention
    lk.unlock();

    // Post-processing (no lock held)
    this_thread::sleep_for(chrono::milliseconds(10));
}
int main(){
    vector<thread> threads;
    for(int i = 1; i <= 5; i++)threads.emplace_back(work, i);
    for(auto &t: threads)t.join();
    return 0;
}