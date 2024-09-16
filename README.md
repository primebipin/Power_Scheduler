# Power Scheduler

## Overview
The Power Scheduler is a C++ application designed to efficiently manage task execution by balancing performance and energy consumption. It schedules tasks based on their priority, power consumption, and the current battery level of the system. The scheduler skips high-power tasks when the battery is low or during peak electricity usage hours.

This project runs on Linux, integrates with `systemd` for service management, and is built using CMake.

## Features
- **Task Scheduling**: Schedule tasks with varying priorities and power consumption.
- **Energy-Aware Scheduling**: Automatically skips high-power tasks when the battery is low or during peak hours.
- **Multi-threaded Execution**: Efficiently handles tasks using multiple threads.
- **`systemd` Integration**: Can be set up as a `systemd` service for automatic startup and management.

## Directory Structure
Power_Scheduler/
├── CMakeLists.txt
├── src/
│ ├── main.cpp
│ ├── scheduler.cpp
│ ├── task.cpp
├── include/
│ ├── scheduler.h
│ └── task.h
└── systemd/
└── scheduler.service

- **src/**: Contains the source files for the application.
- **include/**: Contains the header files for the application.
- **systemd/**: Contains the `systemd` service file for the scheduler.

## Dependencies
- **CMake** (version 3.10 or higher)
- **C++17** compiler
- **pthread** (for multi-threading support)
- **`systemd`** (for service integration)


The scheduler will automatically skip high-power tasks if the battery level falls below a defined threshold or during peak electricity hours.
Multi-threaded Execution

The scheduler manages tasks on multiple threads to ensure efficient execution. The number of threads is configurable within the scheduler implementation.