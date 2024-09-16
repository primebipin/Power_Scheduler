#include "scheduler.h" 
#include "task.h"      
#include <iostream>
#include <chrono>
#include <thread>

void lowPowerTask()
{
    std::cout << "Running a low-power task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void highPowerTask()
{
    std::cout << "Running a high-power task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{
    Scheduler scheduler(20); // Set the low battery threshold to 20%

    // Define tasks
    Task task1("LowPowerTask", Task::LOW, 1, lowPowerTask);
    Task task2("HighPowerTask", Task::HIGH, 2, highPowerTask);
    Task task3("DependentTask", Task::LOW, 3, []()
               { std::cout << "Running a dependent task..." << std::endl; }, {&task1});

    // Add tasks to the scheduler
    scheduler.addTask(task1);
    scheduler.addTask(task2);
    scheduler.addTask(task3);

    // Start the scheduler
    scheduler.start();

    // Run for a certain duration
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop the scheduler
    scheduler.stopScheduler();

    return 0;
}
