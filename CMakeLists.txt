cmake_minimum_required(VERSION 3.10)
project(Power_Scheduler)

set(CMAKE_CXX_STANDARD 17)

# Include the include directory for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Power_Scheduler src/main.cpp src/scheduler.cpp src/task.cpp)
