#include "AudioHandler.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>

AudioHandler::AudioHandler() 
    : playbackState(PlaybackState::PLAYING), 
      wifiState(WiFiState::UNKNOWN),
      previousWifiState(WiFiState::UNKNOWN) {}

void AudioHandler::process() {
    // Only log PLAYING AUDIO when actually playing (not paused)
    if (playbackState == PlaybackState::PLAYING) {
        writeToCSV("PLAYING AUDIO");
    }
}

void AudioHandler::setWiFiStatus(const std::string& status) {
    previousWifiState = wifiState;
    wifiState = stringToWiFiState(status);
    
    // Handle WiFi state transitions - only when playing
    if (playbackState == PlaybackState::PLAYING && previousWifiState != WiFiState::UNKNOWN) {
        if (previousWifiState == WiFiState::DISCONNECTED && wifiState == WiFiState::CONNECTED) {
            writeToCSV("PLAYING AUDIO ONLINE");
        } else if (previousWifiState == WiFiState::CONNECTED && wifiState == WiFiState::DISCONNECTED) {
            writeToCSV("PLAYING AUDIO OFFLINE");
        }
    }
}

void AudioHandler::handleButtonPress(const std::string& button) {
    if (button == "PAUSE") {
        if (playbackState == PlaybackState::PLAYING) {
            playbackState = PlaybackState::PAUSED;
            writeToCSV("PAUSED");
        }
    } else if (button == "PLAY") {
        if (playbackState == PlaybackState::PAUSED) {
            playbackState = PlaybackState::PLAYING;
            // Don't write anything here, let the normal process() handle PLAYING AUDIO
        }
    } else if (button == "NEXT") {
        playbackState = PlaybackState::PLAYING;  // Resume playing when changing tracks
        writeToCSV("PLAYING THE NEXT TRACK");
    } else if (button == "PREVIOUS") {
        playbackState = PlaybackState::PLAYING;  // Resume playing when changing tracks
        writeToCSV("PLAYING THE PREVIOUS TRACK");
    }
}

WiFiState AudioHandler::stringToWiFiState(const std::string& status) {
    if (status == "CONNECTED") return WiFiState::CONNECTED;
    if (status == "DISCONNECTED") return WiFiState::DISCONNECTED;
    return WiFiState::UNKNOWN;
}

void AudioHandler::writeToCSV(const std::string& message) {
    std::ofstream file("../audio.csv", std::ios::app);
    if (!file.is_open()) file.open("audio.csv", std::ios::app);
    
    if (file.is_open()) {
        file << message << std::endl;
        file.close();
        
        long long timestamp = getElapsedTimeMs();
        std::cout << "[" << std::setw(8) << timestamp << "ms] " << message << std::endl;
    } else {
        std::cout << "Error: Could not write to audio.csv file" << std::endl;
    }
}

long long AudioHandler::getElapsedTimeMs() {
    static auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
}
