cmake_minimum_required(VERSION 3.10)
project(AutoClickerTracker)

set(CMAKE_CXX_STANDARD 23)

# Headers
include_directories(include)
include_directories(include/statistics)

# Ensure 'data' folder exists in the build directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

# src
file(GLOB SOURCES "src/*.cpp")
file(GLOB STATISTICS_SOURCES "src/statistics/*.cpp")

# executable
add_executable(AutoClickerTracker ${SOURCES} ${STATISTICS_SOURCES})

# GDI32
target_link_libraries(AutoClickerTracker gdi32)
