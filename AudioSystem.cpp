#include "AudioSystem.h"
#include <iostream>
#include <thread>

AudioSystem::AudioSystem() : running(false) {
    wifiHandler = std::make_unique<WiFiHandler>();
    buttonHandler = std::make_unique<ButtonHandler>();
    audioHandler = std::make_unique<AudioHandler>();
    
    // Set up callbacks for event-driven communication
    wifiHandler->setStatusCallback([this](const std::string& status) {
        onWiFiStatusChange(status);
    });
    
    buttonHandler->setButtonCallback([this](const std::string& button) {
        onButtonPress(button);
    });
}

AudioSystem::~AudioSystem() {
    stop();
}

void AudioSystem::onWiFiStatusChange(const std::string& status) {
    audioHandler->setWiFiStatus(status);
}

void AudioSystem::onButtonPress(const std::string& button) {
    audioHandler->handleButtonPress(button);
}

void AudioSystem::start() {
    if (running.load()) {
        std::cout << "System already running" << std::endl;
        return;
    }
    
    std::cout << "Starting Audio System..." << std::endl;
    
    auto now = std::chrono::steady_clock::now();
    lastWiFiCheck = now;
    lastButtonCheck = now;
    lastAudioProcess = now;
    
    running = true;
    mainThread = std::thread([this]() { mainLoop(); });
    
    std::cout << "Audio System started successfully" << std::endl;
}

void AudioSystem::stop() {
    if (!running.load()) return;
    
    std::cout << "Stopping Audio System..." << std::endl;
    running = false;
    
    if (mainThread.joinable()) {
        mainThread.join();
    }
    
    std::cout << "Audio System stopped" << std::endl;
}

void AudioSystem::mainLoop() {
    std::cout << "Main processing loop started" << std::endl;
    
    // Process first events
    wifiHandler->process();
    buttonHandler->process();
    audioHandler->process();

    while (running.load()) {
        auto currentTime = std::chrono::steady_clock::now();
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                currentTime - lastWiFiCheck).count() >= WIFI_INTERVAL_MS) {
            wifiHandler->process();
            lastWiFiCheck = currentTime;
        }
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                currentTime - lastButtonCheck).count() >= BUTTON_INTERVAL_MS) {
            buttonHandler->process();
            lastButtonCheck = currentTime;
        }
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                currentTime - lastAudioProcess).count() >= AUDIO_INTERVAL_MS) {
            audioHandler->process();
            lastAudioProcess = currentTime;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "Main processing loop ended" << std::endl;
}
