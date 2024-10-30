cmake_minimum_required(VERSION 3.29)

project(ModPlayerExample)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ModPlayer)

if (TARGET_PLATFORM STREQUAL "Linux")
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif()
