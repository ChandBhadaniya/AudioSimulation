cmake_minimum_required(VERSION 3.10)
project(AudioSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AudioSystem 
    main.cpp
    AudioSystem.cpp
    WiFiHandler.cpp
    ButtonHandler.cpp
    AudioHandler.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(AudioSystem Threads::Threads)