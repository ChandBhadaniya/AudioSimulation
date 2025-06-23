#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <string>
#include <vector>
#include <functional>

class ButtonHandler {
public:
    using ButtonPressCallback = std::function<void(const std::string&)>;
    
    ButtonHandler();
    void process();
    void setButtonCallback(ButtonPressCallback callback);
    
private:
    std::vector<std::string> buttonData;
    size_t buttonIndex;
    std::string lastButton;
    ButtonPressCallback buttonCallback;
    
    void loadData();
    void handlePress(const std::string& button);
};

#endif // BUTTON_HANDLER_H
