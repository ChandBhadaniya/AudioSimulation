#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include <string>
#include <chrono>

enum class PlaybackState {
    PLAYING,
    PAUSED
};

enum class WiFiState {
    CONNECTED,
    DISCONNECTED,
    UNKNOWN
};

class AudioHandler {
public:
    AudioHandler();
    void process();
    void setWiFiStatus(const std::string& status);
    void handleButtonPress(const std::string& button);
    
private:
    PlaybackState playbackState;
    WiFiState wifiState;
    WiFiState previousWifiState;
    
    void writeToCSV(const std::string& message);
    long long getElapsedTimeMs();
    WiFiState stringToWiFiState(const std::string& status);
};

#endif // AUDIO_HANDLER_H
