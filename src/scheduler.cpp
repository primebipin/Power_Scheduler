#include <scheduler.h>
#include <iostream>
#include <cstdlib>

Scheduler::Scheduler(int lowBatteryThreshold)
    : lowBatteryThreshold(lowBatteryThreshold), stop(false) {}

void Scheduler::addTask(const Task &task)
{
    std::lock_guard<std::mutex> lock(mutex);
    taskQueue.push(task);
    condition.notify_one();
}

void Scheduler::start()
{
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        workers.emplace_back(&Scheduler::workerThread, this);
    }
}

void Scheduler::stopScheduler()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        stop = true;
        condition.notify_all();
    }

    for (std::thread &worker : workers)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

Task Scheduler::getTask()
{
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [this]
                   { return !taskQueue.empty() || stop; });

    if (stop && taskQueue.empty())
    {
        return Task("", Task::LOW, 0, []() {});
    }

    Task task = taskQueue.top();
    taskQueue.pop();
    return task;
}

void Scheduler::workerThread()
{
    while (true)
    {
        Task task = getTask();
        if (stop)
            return;

        int batteryLevel = getBatteryLevel();
        if (batteryLevel <= lowBatteryThreshold && task.getPowerConsumption() == Task::HIGH)
        {
            std::cout << "Skipping high-power task due to low battery..." << std::endl;
        }
        else
        {
            task.run();
        }
    }
}

int Scheduler::getBatteryLevel()
{
    FILE *pipe = popen("upower -i $(upower -e | grep BAT) | grep percentage | awk '{print $2}' | tr -d '%'", "r");
    if (!pipe)
        return -1;
    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    pclose(pipe);
    return std::stoi(result);
}
