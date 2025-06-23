#include "ButtonHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

ButtonHandler::ButtonHandler() : buttonIndex(0), lastButton("") {
    loadData();
}

void ButtonHandler::setButtonCallback(ButtonPressCallback callback) {
    buttonCallback = callback;
}

void ButtonHandler::loadData() {
    std::ifstream file("../button.csv");
    if (!file.is_open()) file.open("button.csv");
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not open button.csv file" << std::endl;
        return;
    }
    
    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string button;
        
        while (std::getline(ss, button, ',')) {
            button.erase(0, button.find_first_not_of(" \t\r\n"));
            button.erase(button.find_last_not_of(" \t\r\n") + 1);
            if (!button.empty()) buttonData.push_back(button);
        }
    }
    
    file.close();
    std::cout << "Loaded " << buttonData.size() << " button values" << std::endl;
}

void ButtonHandler::process() {
    if (buttonData.empty()) return;
    
    std::string currentButton = buttonData[buttonIndex];
    buttonIndex = (buttonIndex + 1) % buttonData.size();
    
    if (currentButton != lastButton && !currentButton.empty()) {
        std::cout << "Button Pressed: " << currentButton << std::endl;
        handlePress(currentButton);
        lastButton = currentButton;
    }
}

void ButtonHandler::handlePress(const std::string& button) {
    if (buttonCallback) {
        buttonCallback(button);
    }
}
