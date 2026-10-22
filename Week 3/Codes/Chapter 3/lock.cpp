#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;

mutex m1, m2;
int sum = 0;
int square = 0;
void work(int i){
    lock(m1, m2); // Aqquire Both at the same time avoiding deadlock

    // The mutex is already locked by this thread.
    // Just take responsibility for unlocking it. lock_guard<mutex> l1(m1, adopt_lock);
    lock_guard<mutex> l1(m1, adopt_lock);
    lock_guard<mutex> l2(m2, adopt_lock);
    sum += i;
    square += i * i;

    cout << "Worker " << i << " updated:" << "(" << sum << "," << square << ")\n";

}
int main(){
    vector<thread> threads;
    for(int i = 1; i <= 5; i++){
        threads.emplace_back(work, i);
    }
    for(auto &t: threads){
        t.join();
    }
    return 0;
}