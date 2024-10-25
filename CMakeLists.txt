cmake_minimum_required(VERSION 3.29)
project(ModPlayer)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    src/Arpeggio.cpp
    src/Arpeggio.hpp
    src/Channel.cpp
    src/Channel.hpp
    src/CombinedEffect.cpp
    src/CombinedEffect.hpp
    src/Effect.hpp
    src/main.cpp
    src/Module.cpp
    src/Module.hpp
    src/SlideDown.hpp
    src/SlideDown.cpp
    src/SlideToNote.hpp
    src/SlideToNote.cpp
    src/SlideUp.cpp
    src/SlideUp.hpp
    src/Vibrato.cpp
    src/Vibrato.hpp
    src/VolumeSlide.cpp
    src/VolumeSlide.hpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
