
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class IPaymentStrategy
{
public:
    virtual void pay(double amount) = 0;
    virtual ~IPaymentStrategy() = default;
};

class CreditCardPayment : public IPaymentStrategy
{
public:
    void pay(double amount) override
    {
        cout << "Using [Credit Card] to pay: " << amount << "\n";
    }
};

class UpiCardPayment : public IPaymentStrategy
{
public:
    void pay(double amount) override
    {
        cout << "Using [UPI] to pay: " << amount << "\n";
    }
};

class WalltetPayment : public IPaymentStrategy
{
public:
    void pay(double amount) override
    {
        cout << "Using [Wallet] to pay: " << amount << "\n";
    }
};

class PaymentFactory
{
public:
    static IPaymentStrategy *createPayement(string method)
    {
        if (method == "CreditCard")
            return new CreditCardPayment();
        else if (method == "Upi")
            return new UpiCardPayment();
        else if (method == "Wallet")
            return new WalltetPayment();
        else
            throw invalid_argument("No such payment strategy");
    }
};

class IDiscountStrategy
{
public:
    virtual double apply(double amount) = 0;
    virtual ~IDiscountStrategy() = default;
};

class CouponDiscount : public IDiscountStrategy
{
private:
    double rate;

public:
    CouponDiscount(double rate = 0.9) : rate(rate) {}

    double apply(double amount) override
    {
        cout << "Coupon Discount: " << amount * rate << "\n";
        return amount * rate;
    }
};

class FestivalDiscount : public IDiscountStrategy
{
private:
    double rate;

public:
    FestivalDiscount(double rate = 0.7) : rate(rate) {}

    double apply(double amount) override
    {
        cout << "Festival Discount: " << amount * rate << "\n";
        return amount * rate;
    }
};

class LoyaltyDiscount : public IDiscountStrategy
{
private:
    double rate;

public:
    LoyaltyDiscount(double rate = 0.5) : rate(rate) {}

    double apply(double amount) override
    {
        cout << "Loyalty Discount: " << amount * rate << "\n";
        return amount * rate;
    }
};

class DiscountFactory
{
public:
    static IDiscountStrategy *createDiscount(string strategy)
    {
        if (strategy == "Coupon")
            return new CouponDiscount();
        else if (strategy == "Festival")
            return new FestivalDiscount();
        else if (strategy == "Loyalty")
            return new LoyaltyDiscount();
        else
            throw invalid_argument("No such discount strategy");
    }
};

class CheckoutService
{
private:
    IPaymentStrategy *payment;
    IDiscountStrategy *discount;

public:
    CheckoutService(IPaymentStrategy *payment,
                    IDiscountStrategy *discount)
        : payment(payment), discount(discount) {}

    void checkout(double amount)
    {
        double finalAmount = discount->apply(amount);
        payment->pay(finalAmount);
    }
};

int main()
{
    try
    {
        IPaymentStrategy *p =
            PaymentFactory::createPayement("Upi");

        IDiscountStrategy *d =
            DiscountFactory::createDiscount("Festival");

        CheckoutService c(p, d);

        c.checkout(1000);

        delete p;
        delete d;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
