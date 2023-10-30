cmake_minimum_required(VERSION 3.10)

project(TanksGame VERSION 0.1.0)
set(EXECUTABLE_NAME TanksGame)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
# produce non-optimized code with debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Find necessary libraries
# Add libraries here like this: find_package(SDL2 REQUIRED)

# Add source files and headers
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# Include directories like this: include_directories(${SDL2_INCLUDE_DIRS})

# Create an executable
add_executable(${EXECUTABLE_NAME})
target_sources(${EXECUTABLE_NAME} PUBLIC ${SOURCES})

# Link libraries like this: target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Set the project include directories
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

# Enable all compiler warnings
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)



