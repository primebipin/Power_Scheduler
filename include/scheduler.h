#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "task.h"

struct TaskComparator
{
    bool operator()(const Task &a, const Task &b)
    {
        return a.getPriority() < b.getPriority();
    }
};

class Scheduler
{
public:
    Scheduler(int lowBatteryThreshold);
    void addTask(const Task &task);
    void start();
    void stopScheduler();
    int getBatteryLevel();

private:
    std::priority_queue<Task, std::vector<Task>, TaskComparator> taskQueue;
    std::vector<std::thread>workers;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop;
    int lowBatteryThreshold;
    void workerThread();
    Task getTask();
};

#endif