cmake_minimum_required(VERSION 3.24)
project(pixelProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(SFML)
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SRCH "*.h")
file(GLOB SRCCXX ".cpp")
source_group("" FILES ${SRCCXX} ${SRCH})

add_executable(pixelProject main.cpp)
target_link_libraries(pixelProject PRIVATE SFML::Graphics)