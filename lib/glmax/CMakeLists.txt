cmake_minimum_required(VERSION 3.14)
project(glmax)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)

# Add cpp files
add_library(stb_image third-party/stb_image.cpp)
add_library(glmax ${SRC_FILES})

# Add hpp files
target_include_directories(glmax PUBLIC src third-party)
target_link_libraries(glmax PRIVATE stb_image)

# Add glm
target_include_directories(glmax PUBLIC third-party/glm)

# Add quick_imgui for glad
target_link_libraries(glmax PUBLIC quick_imgui)

