#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex guardedMutex;
int guardedValue = 0;

void tryWorker(int id) {
    // try_to_lock makes one non-blocking attempt to acquire the mutex.
    unique_lock<mutex> lock(guardedMutex, try_to_lock);
    if (lock.owns_lock()) {
        guardedValue += id;
        cout << "[try_to_lock] Thread " << id
                  << " acquired the lock; value = " << guardedValue << '\n';
    } else {
        cout << "[try_to_lock] Thread " << id
                  << " found the lock busy; doing fallback work\n";
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

int main() {
    // Hold the mutex briefly so the workers can demonstrate failed attempts.
    thread blocker([] {
        lock_guard<mutex> lock(guardedMutex);
        cout << "[blocker] Holding the lock\n";
        this_thread::sleep_for(chrono::milliseconds(60));
        cout << "[blocker] Releasing the lock\n";
    });

    this_thread::sleep_for(chrono::milliseconds(5));

    vector<thread> workers;
    for (int id = 1; id <= 3; ++id) {
        workers.emplace_back(tryWorker, id);
    }

    blocker.join();
    for (auto& worker : workers) {
        worker.join();
    }

    cout << "Final guarded value = " << guardedValue << '\n';
}

