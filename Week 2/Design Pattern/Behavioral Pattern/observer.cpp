
#include <iostream>
#include <list>
#include <string>
using namespace std;

class IObserver
{
public:
    virtual void update() = 0;
    virtual ~IObserver() = default;
};

class NewChannel : public IObserver
{
private:
    string _name = "Default";

public:
    NewChannel(string name) : _name(name) {}

    void update() override
    {
        cout << "News Channel " << _name << " is Updated\n";
    }
};

class ISubject
{
public:
    virtual void addObserver(IObserver *o) = 0;
    virtual void removeObserver(IObserver *o) = 0;
    virtual void notifyObserver() = 0;
    virtual ~ISubject() = default;
};

class NewsAgency : public ISubject
{
private:
    string news;
    list<IObserver *> observers;

public:
    void setNews(string news)
    {
        this->news = news;
        notifyObserver();
    }

    void addObserver(IObserver *o) override
    {
        observers.push_back(o);
    }

    void removeObserver(IObserver *o) override
    {
        observers.remove(o);
    }

    void notifyObserver() override
    {
        for (IObserver *o : observers)
        {
            o->update();
        }
    }
};

int main()
{
    NewsAgency agency;

    NewChannel c1("NDTV");
    NewChannel c2("CNN");
    NewChannel c3("BBC");

    agency.addObserver(&c1);
    agency.addObserver(&c2);
    agency.addObserver(&c3);

    agency.setNews("Breaking News");

    cout << "\nRemoving CNN...\n \n";
    agency.removeObserver(&c2);

    agency.setNews("Latest News");

    return 0;
}
