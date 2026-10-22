#include<iostream>
#include<thread>
#include<chrono>
#include<memory>
using namespace std;

// Issue

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;
/*
int main()
{
    string msg = "hello, world";

    // [&] captures msg by reference, not by value
    thread t([&]()
             {
        // Worker waits for 150 ms
        this_thread::sleep_for(chrono::milliseconds(150));

        // ISSUE: msg may already be destroyed when this executes
        // Accessing a destroyed object causes Undefined Behavior (UB)
        cout << "[worker] msg = " << msg << "\n"; });

    // ISSUE: detach() allows worker to run independently
    // Main does not wait for the worker to finish
    t.detach();

    cout << "[main] exiting; worker may still be running...\n";

    // ISSUE: msg is destroyed when main's scope ends
    // Worker may still hold a dangling reference to msg
    // Also, returning from main terminates the process
    return 0;
}
*/
// Solution

/*
Use Shared Pointer to avoid that problem
*/
// Fix
int main()
{
    auto s = make_shared<string>("Hello World");

    thread t([s]() { // Capture shared_ptr by value
        this_thread::sleep_for(chrono::milliseconds(150));
        cout << "Worker: " << *s << "\n";
    });

    t.detach();
    s.reset(); // Safe: worker owns another shared_ptr

    cout << "[main] dropped my ref; worker still has it safely\n";
    this_thread::sleep_for(chrono::milliseconds(250));
    cout << "[main] exit\n";

    return 0;
}