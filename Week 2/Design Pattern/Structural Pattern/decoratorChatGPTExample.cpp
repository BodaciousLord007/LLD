#include <iostream>
using namespace std;

// 1. Component Interface
class Coffee
{
public:
    virtual int getCost() = 0;
    virtual string getDescription() = 0;
    virtual ~Coffee() = default;
};

// 2. Concrete Component
class SimpleCoffee : public Coffee
{
public:
    int getCost() override
    {
        return 50;
    }

    string getDescription() override
    {
        return "Simple Coffee";
    }
};

// 3. Base Decorator
class CoffeeDecorator : public Coffee
{
protected:
    Coffee *coffee;

public:
    CoffeeDecorator(Coffee *c) : coffee(c) {}

    int getCost() override
    {
        return coffee->getCost();
    }

    string getDescription() override
    {
        return coffee->getDescription();
    }

    ~CoffeeDecorator() override
    {
        delete coffee;
    }
};

// 4. Milk Decorator
class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(Coffee *c) : CoffeeDecorator(c) {}

    int getCost() override
    {
        return coffee->getCost() + 20;
    }

    string getDescription() override
    {
        return coffee->getDescription() + " + Milk";
    }
};

// 5. Sugar Decorator
class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(Coffee *c) : CoffeeDecorator(c) {}

    int getCost() override
    {
        return coffee->getCost() + 10;
    }

    string getDescription() override
    {
        return coffee->getDescription() + " + Sugar";
    }
};

// 6. Chocolate Decorator
class ChocolateDecorator : public CoffeeDecorator
{
public:
    ChocolateDecorator(Coffee *c) : CoffeeDecorator(c) {}

    int getCost() override
    {
        return coffee->getCost() + 40;
    }

    string getDescription() override
    {
        return coffee->getDescription() + " + Chocolate";
    }
};

void printCoffee(Coffee *coffee)
{
    cout << coffee->getDescription() << "\n";
    cout << "Cost: " << coffee->getCost() << "\n\n";
}

int main()
{

    // Combo 1: Simple Coffee
    Coffee *coffee1 = new SimpleCoffee();
    printCoffee(coffee1);

    // Combo 2: Coffee + Milk
    Coffee *coffee2 = new MilkDecorator(
        new SimpleCoffee());
    printCoffee(coffee2);

    // Combo 3: Coffee + Sugar
    Coffee *coffee3 = new SugarDecorator(
        new SimpleCoffee());
    printCoffee(coffee3);

    // Combo 4: Coffee + Milk + Sugar
    Coffee *coffee4 = new SugarDecorator(
        new MilkDecorator(
            new SimpleCoffee()));
    printCoffee(coffee4);

    // Combo 5: Coffee + Milk + Chocolate
    Coffee *coffee5 = new ChocolateDecorator(
        new MilkDecorator(
            new SimpleCoffee()));
    printCoffee(coffee5);

    // Combo 6: Coffee + Milk + Sugar + Chocolate
    Coffee *coffee6 = new ChocolateDecorator(
        new SugarDecorator(
            new MilkDecorator(
                new SimpleCoffee())));
    printCoffee(coffee6);

    // Combo 7: Coffee + Double Milk + Sugar
    Coffee *coffee7 = new SugarDecorator(
        new MilkDecorator(
            new MilkDecorator(
                new SimpleCoffee())));
    printCoffee(coffee7);

    // Cleanup (each decorator owns its wrapped object)
    delete coffee1;
    delete coffee2;
    delete coffee3;
    delete coffee4;
    delete coffee5;
    delete coffee6;
    delete coffee7;

    return 0;
}
