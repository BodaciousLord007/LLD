#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex mutexA;
mutex mutexB;
int valueA = 0;
int valueB = 0;

void updateBoth(int id) {
    // Lock both mutexes without risking a lock-order deadlock.
    lock(mutexA, mutexB);

    // adopt_lock tells each unique_lock that its mutex is already locked.
    unique_lock<mutex> lockA(mutexA, adopt_lock);
    unique_lock<mutex> lockB(mutexB, adopt_lock);

    valueA += id;
    valueB += id * 2;
    cout << "[adopt_lock] Thread " << id << " updated values: a="
              << valueA << ", b=" << valueB << '\n';
    // The unique_lock destructors release both mutexes.
}

int main() {
    vector<thread> threads;
    for (int id = 1; id <= 4; ++id) {
        threads.emplace_back(updateBoth, id);
    }
    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Final values: a=" << valueA << ", b=" << valueB << '\n';
}

