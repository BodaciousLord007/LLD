#include<iostream>
using namespace std;

class INotification{
public:
    ~INotification() = default;
    virtual void send(string to, string message) = 0;
};
class EmailNotication: public INotification{
public:
    void send(string to, string message) override{
        cout << "Sending Email to " << to << ":" << message << "\n";
    };
};
class SmsNotication : public INotification
{
public:
    void send(string to, string message) override
    {
        cout << "Sending SMS to " << to << ":" << message << "\n";
    };
};
class PushNotication : public INotification
{
public:
    void send(string to, string message) override
    {
        cout << "Sending push to " << to << ":" << message << "\n";
    };
};

class NotificationFactory{
public:
    static INotification* create(string channel){
        if(channel == "Email")return new EmailNotication;
        else if(channel == "Sms")return new SmsNotication;
        else if(channel == "Push")return new PushNotication;
        else throw invalid_argument("Invalid Channel");
    }
};
int main()
{
    INotification *email = NotificationFactory::create("Email");
    INotification *sms = NotificationFactory::create("Sms");
    INotification *push = NotificationFactory::create("Push");

    email->send("abc@gmail.com", "Hello!");
    sms->send("9876543210", "Your OTP is 1234");
    push->send("User123", "You have a new notification");

    delete email;
    delete sms;
    delete push;

    // To Check Error
    // INotification *other = NotificationFactory::create("abc");
    return 0;
}