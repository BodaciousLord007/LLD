
#include <iostream>
using namespace std;

// 1. Interface
class INotification
{
public:
    virtual void send(string to, string message) = 0;
    virtual ~INotification() = default;
};

// 2. Concrete Component
class EmailNotification : public INotification
{
public:
    void send(string to, string message) override
    {
        cout << "[EMAIL] To: " << to
             << " | Message: " << message << "\n";
    }
};

// 3. Abstract Decorator
class NotificationDecorator : public INotification
{
protected:
    INotification *wrappee;

public:
    NotificationDecorator(INotification *n)
        : wrappee(n) {}

    void send(string to, string message) override
    {
        wrappee->send(to, message);
    }

    virtual ~NotificationDecorator()
    {
        delete wrappee;
    }
};

// 4. Concrete Decorator
class LoggingNotification : public NotificationDecorator
{
public:
    LoggingNotification(INotification *n)
        : NotificationDecorator(n) {}

    void send(string to, string message) override
    {
        cout << "[LOG] Starting notification...\n";

        wrappee->send(to, message);

        cout << "[LOG] Notification completed.\n";
    }
};

int main()
{

    // Example 1: Only Email
    cout << "Example 1: Email Only\n";

    INotification *n1 = new EmailNotification();

    n1->send("user@gmail.com", "Hello!");
    delete n1;

    cout << "\n";

    // Example 2: Email + Logging
    cout << "Example 2: Email + Logging\n";

    INotification *n2 = new LoggingNotification(
        new EmailNotification());

    n2->send("user@gmail.com", "Welcome!");
    delete n2;

    cout << "\n";

    // Example 3: Email + Double Logging
    cout << "Example 3: Email + Double Logging\n";

    INotification *n3 = new LoggingNotification(
        new LoggingNotification(
            new EmailNotification()));

    n3->send("user@gmail.com", "Payment Successful!");
    delete n3;

    return 0;
}
