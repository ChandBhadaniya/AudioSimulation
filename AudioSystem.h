#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <atomic>
#include <memory>
#include <thread>
#include <chrono>
#include "WiFiHandler.h"
#include "ButtonHandler.h"
#include "AudioHandler.h"

class AudioSystem {
private:
    std::atomic<bool> running;
    std::thread mainThread;
    
    // Modules
    std::unique_ptr<WiFiHandler> wifiHandler;
    std::unique_ptr<ButtonHandler> buttonHandler;
    std::unique_ptr<AudioHandler> audioHandler;
    
    // Timing
    std::chrono::steady_clock::time_point lastWiFiCheck;
    std::chrono::steady_clock::time_point lastButtonCheck;
    std::chrono::steady_clock::time_point lastAudioProcess;
    
    // Constants
    static constexpr int WIFI_INTERVAL_MS = 100;
    static constexpr int BUTTON_INTERVAL_MS = 10000;
    static constexpr int AUDIO_INTERVAL_MS = 100;

public:
    AudioSystem();
    ~AudioSystem();
    
    void start();
    void stop();
    bool isRunning() const { return running.load(); }
    
private:
    void mainLoop();
    void onWiFiStatusChange(const std::string& status);
    void onButtonPress(const std::string& button);
    
    AudioSystem(const AudioSystem&) = delete;
    AudioSystem& operator=(const AudioSystem&) = delete;
};

#endif // AUDIO_SYSTEM_H
