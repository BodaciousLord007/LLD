#include<iostream>
using namespace std;

class IPaymentStrategy{
public:
    virtual void pay(int amount) = 0;
};
class CardPayment:public IPaymentStrategy{
public:
    void pay(int amount)override{
        cout << "Using Card to pay:" << amount << "\n";
    };
};
class UpiPayment:public IPaymentStrategy{
    void pay(int amount) override{
        cout << "Using Card to pay:" << amount << "\n";
    };
};
class ShoppingPattern{
private:
    IPaymentStrategy* strategy;
public:
    void setPaymentStrategy(IPaymentStrategy* strategy){
        this->strategy = strategy;
    };
    void check(int amount){
        strategy->pay(amount);
    }
};
int main(){
    ShoppingPattern* p = new ShoppingPattern;
    CardPayment* card = new CardPayment;
    UpiPayment* upi = new UpiPayment;

    p->setPaymentStrategy(card);
    p->check(100);
    
    p->setPaymentStrategy(upi);
    p->check(150);
    return 0;
}