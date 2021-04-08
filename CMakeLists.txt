cmake_minimum_required(VERSION 3.17)
project(MachineVision)

set(OpenCV_DIR "/Users/matthewmunson/opencv_build")
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(MachineVision Assignment1/Program1.cpp Assignment1/Program1.h Assignment1/main.cpp)

target_link_libraries(MachineVision ${OpenCV_LIBS})
