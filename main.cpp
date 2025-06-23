#include <iostream>
#include "AudioSystem.h"

int main() {
    std::cout << "Starting Audio System Simulation..." << std::endl;
    std::cout << "Make sure wifi.csv and button.csv files exist." << std::endl;
    std::cout << "Press Enter to stop the simulation..." << std::endl;
    
    AudioSystem system;
    system.start();
    
    std::cin.get();
    
    std::cout << "Stopping simulation..." << std::endl;
    system.stop();
    
    std::cout << "Simulation stopped. Check audio.csv for output." << std::endl;
    return 0;
}