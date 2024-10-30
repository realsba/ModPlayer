cmake_minimum_required(VERSION 3.29)

project(ModPlayer)

set(CMAKE_CXX_STANDARD 23)

if(NOT DEFINED TARGET_PLATFORM)
    set(TARGET_PLATFORM "Linux" CACHE STRING "Target platform")
endif()

add_library(${PROJECT_NAME} STATIC
    src/Arpeggio.cpp
    src/Channel.cpp
    src/CombinedEffect.cpp
    src/Module.cpp
    src/SlideDown.cpp
    src/SlideToNote.cpp
    src/SlideUp.cpp
    src/Vibrato.cpp
    src/VolumeSlide.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (TARGET_PLATFORM STREQUAL "Linux")
    add_subdirectory(examples)
endif()