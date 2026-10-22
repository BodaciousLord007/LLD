#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex sharedMutex;
int sharedValue = 0;

void worker(int id) {
    const int localValue = id * 10;

    // Prepare the lock now, but acquire the mutex only when needed.
    unique_lock<mutex> lock(sharedMutex, defer_lock);
    this_thread::sleep_for(chrono::milliseconds(5));
    lock.lock();

    sharedValue += localValue;
    cout << "[defer_lock] Thread " << id << " added " << localValue
              << "; shared value = " << sharedValue << '\n';

    // Release before doing work that does not need the mutex.
    lock.unlock();
    this_thread::sleep_for(chrono::milliseconds(5));
}

int main() {
    vector<thread> threads;
    for (int id = 1; id <= 4; ++id) {
        threads.emplace_back(worker, id);
    }
    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Final shared value = " << sharedValue << '\n';
}

