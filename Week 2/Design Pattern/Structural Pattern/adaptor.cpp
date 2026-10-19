#include<iostream>
using namespace std;

class IPaymentProcessor{
public:
    ~IPaymentProcessor() = default;
    virtual double processPayment(double amount) = 0;    
};

class OldPaymentService{
public:
    double makePaymentInPaise(double paise){
        return 0.0f;
    }
};
class oldPaymentAdaptar: public IPaymentProcessor{
private:
    OldPaymentService* service = NULL;
public:
    oldPaymentAdaptar(OldPaymentService* service):service(service){};
    double processPayment(double payment){
        return service->makePaymentInPaise(payment);
    }
};
int main(){
    OldPaymentService *service = new OldPaymentService();
    oldPaymentAdaptar *adap = new oldPaymentAdaptar(service);
    adap->processPayment(100);
    return 0;
}