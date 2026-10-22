#include<iostream>
#include<thread>
#include<vector>

using namespace std;

int main()
{
    vector<int> big(1'000'000, 42);
    int i = 7;

    //Over-capturing by value: copies the whole 'big' vector into the lambda
    // auto heavy = thread([=](){cout << "[heavy] size = " << big.size() << ", i = " << i << "\n"; });

    //Precise capture: only capture what you need (by value or ref)
    auto light = thread([i]() { // don't pull in 'big' at all
        std::cout << "[light] i = " << i << "\n";
    });

    // heavy.join();
    light.join();
    return 0;
}