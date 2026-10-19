#include<iostream>
using namespace std;

class Light{
public:
    void on(){
        cout << "Turn [ON] the light\n";
    }
    void off(){
        cout << "Turn [OFF] the light\n";
    }
};

class ICommand{
public:
    virtual void execute() = 0;
};
class LightOnCommand: public ICommand{
private:
    Light* light;
public:
    LightOnCommand(Light *light) : light(light) {};
    void execute() override{
        light->on();
    }
};
class LightOffCommand: public ICommand
{
private:
    Light *light;

public:
    LightOffCommand(Light* light):light(light){};
    void execute() override
    {
        light->off();
    }
};
class RemoteControl{
private:
    ICommand* command;
public:
    void setCommand(ICommand* command){
        this->command = command;
    };
    void execute(){
        command->execute();
    }
};
int main(){
    Light* light = new Light;
    RemoteControl* remote = new RemoteControl;

    remote->setCommand(new LightOnCommand(light));
    remote->execute();
    remote->setCommand(new LightOffCommand(light));
    remote->execute();
    return 0;
}