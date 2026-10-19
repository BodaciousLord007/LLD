#include<iostream>
using namespace std;

class Logger{
private:
    Logger() = default; // Private Constructor
    Logger(const Logger&) = delete; // No Copy Constructor
    Logger& operator = (const Logger&) = delete; // No Copy Assignment 
public:
    static Logger& getInstance(){
        static Logger instance;// Create once -> Thread Safe
        return instance;
    }
    void info(string msg){
        cout << "INFO:" << msg << "\n";
    }
    void error(string msg)
    {
        cout << "EROR:" << msg << "\n";
    }
};
int main(){
    Logger::getInstance().info("Server Started");
    Logger::getInstance().error("Server Crashed");
    return 0;
}