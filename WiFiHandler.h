#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <string>
#include <vector>
#include <functional>

class WiFiHandler {
public:
    using WiFiStatusCallback = std::function<void(const std::string&)>;
    
    WiFiHandler();
    void process();
    void setStatusCallback(WiFiStatusCallback callback);
    
private:
    std::vector<std::string> wifiData;
    size_t wifiIndex;
    std::string lastStatus;
    std::string currentStatus;
    WiFiStatusCallback statusCallback;
    
    void loadData();
    void handleStatusChange(const std::string& status);
};

#endif // WIFI_HANDLER_H
