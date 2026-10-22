#include <iostream>

#include "Jobs.hpp"
#include "SingleThreadJobEngine.hpp"

using namespace std;
void print(JobResult j){
    std::cout << "Success:" << std::boolalpha << j.success << "\n";
    std::cout << "Message:" << j.message << "\n";
    std::cout << "Value:" << j.value << "\n";
}
int main(){
    SingleThreadJobEngine jbEngine;
    sumRangeJob s(1, 10);
    primeCountJob p(1, 100);
    failingJob f;

    // f.run();

    return 0;
}
