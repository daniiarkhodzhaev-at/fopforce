cmake_minimum_required(VERSION 3.13)  # CMake version check
project(fopforce)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/Display.cpp
        include/Display.h
        src/RandomNumberGenerator.cpp
        include/RandomNumberGenerator.h
        src/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(fopforce ${SOURCE_FILES})

target_link_libraries(fopforce -lfreeglut -lopengl32 -lglu32)
#link_directories(${OPENGL_gl_LIBRARY})
#target_link_libraries(fopforce freeglut glu32 opengl32)