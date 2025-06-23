#include "WiFiHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

WiFiHandler::WiFiHandler() : wifiIndex(0), lastStatus(""), currentStatus("") {
    loadData();
}

void WiFiHandler::setStatusCallback(WiFiStatusCallback callback) {
    statusCallback = callback;
}

void WiFiHandler::loadData() {
    std::ifstream file("../wifi.csv");
    if (!file.is_open()) file.open("wifi.csv");
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not open wifi.csv file" << std::endl;
        return;
    }
    
    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string status;
        
        while (std::getline(ss, status, ',')) {
            status.erase(0, status.find_first_not_of(" \t\r\n"));
            status.erase(status.find_last_not_of(" \t\r\n") + 1);
            if (!status.empty()) wifiData.push_back(status);
        }
    }
    
    file.close();
    std::cout << "Loaded " << wifiData.size() << " WiFi status values" << std::endl;
}

void WiFiHandler::process() {
    if (wifiData.empty()) return;
    
    currentStatus = wifiData[wifiIndex];
    wifiIndex = (wifiIndex + 1) % wifiData.size();
    
    if (currentStatus != lastStatus && !currentStatus.empty()) {
        std::cout << "WiFi Status Changed: " << currentStatus << std::endl;
        handleStatusChange(currentStatus);
        lastStatus = currentStatus;
    }
}

void WiFiHandler::handleStatusChange(const std::string& status) {
    if (statusCallback) {
        statusCallback(status);
    }
}
