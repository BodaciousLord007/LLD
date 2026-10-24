#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct Object {
    string value;
};

class MixpanelSdk {
public:
    void track(string name, Object data) const {
        cout << "Mixpanel tracked " << name << ": " << data.value << '\n';
    }
};

class InternalAnalyticsSdk {
public:
    void track(string name, Object data) const {
        cout << "Internal analytics Tracked "
                  << name << ": " << data.value << '\n';
    }
};

// Metric Client
class MetricClient {
public:
    virtual ~MetricClient() = default;
    virtual void trackEvent(string name, Object data) = 0;
};

class MixpanelAdapter : public MetricClient {
private:
    MixpanelSdk mpSdk;

public:
    MixpanelAdapter(MixpanelSdk sdk = {}) : mpSdk(sdk) {}

    void trackEvent(string name, Object data) override {
        mpSdk.track(name, data);
    }
};

class InternalAnalyticsAdapter : public MetricClient {
private:
    InternalAnalyticsSdk internalSdk;

public:
    InternalAnalyticsAdapter(InternalAnalyticsSdk sdk = {})
        : internalSdk(sdk) {}

    void trackEvent(string name, Object data) override {
        internalSdk.track(name, data);
    }
};

// Metrix Strategy
class MetricStrategy{
public:
    virtual void sendEvent(string name, Object data) = 0;
};
class SingleProviderStrategy:public MetricStrategy{
private:
    MetricClient& client;
public:
    SingleProviderStrategy(MetricClient &client): client(client) {};
    void sendEvent(string name, Object data){
        client.trackEvent(name, data);
    }
};
class MultiProviderStrategy: public MetricStrategy{
private:
    list<MetricClient>&clients;
public:
    MultiProviderStrategy(list<MetricClient>& clients):clients(clients){};
    void sendEvent(string name, Object data){
        for(auto &client: clients){
            client.trackEvent(name, data);
        }
    }
};

//Metrix Manager
class MetrixManager{
private:
    MetricStrategy *strategy = nullptr;

public:
    void setStrategy(MetricStrategy& newStrategy){
        strategy = &newStrategy;
    }
    void track(string name, Object data){
        strategy->sendEvent(name, data);
    }
};

//Metric Decorator
class MetricDecorator : public MetricClient {
protected:
    MetricClient& wrappee;
public:
    MetricDecorator(MetricClient& wrappee) : wrappee(wrappee) {}
};

class LoggingMetricsDecorator : public MetricDecorator {
public:
    LoggingMetricsDecorator(MetricClient& wrappee)
        : MetricDecorator(wrappee) {}

    void trackEvent(string name, Object data) override {
        cout << "Logging metric event: " << name
             << ", data: " << data.value << '\n';
        wrappee.trackEvent(name, data);
    }
};

class BufferedMetricsDecorator: public MetricDecorator{
private:
    struct MetricEvent {
        string name;
        Object data;
    };
    vector<MetricEvent> buffer;

public:
    BufferedMetricsDecorator(MetricClient& wrappee)
        : MetricDecorator(wrappee) {}

    void trackEvent(string name, Object data) override {
        buffer.push_back({name, data});
    }

    void flush() {
        for (const auto& event : buffer) {
            wrappee.trackEvent(event.name, event.data);
        }
        buffer.clear();
    }
};
int main() {
    MixpanelAdapter mixpanel;
    InternalAnalyticsAdapter internalAnalytics;

    LoggingMetricsDecorator loggingClient(mixpanel);
    BufferedMetricsDecorator bufferedClient(internalAnalytics);

    loggingClient.trackEvent("button_clicked", {"signup"});

    bufferedClient.trackEvent("page_viewed", {"home"});
    bufferedClient.trackEvent("purchase_completed", {"order-123"});
    bufferedClient.flush();
    return 0;
}
