#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <functional>
#include <vector>

class Task
{
public:
    enum PowerConsumption
    {
        LOW,
        HIGH
    };

    Task(std::string name, PowerConsumption power, int priority, std::function<void()> exec, std::vector<Task *> dependencies = {}) : name(name), powerConsumption(power), priority(priority), execute(exec), dependencies(dependencies) {};

    int getPriority() const
    {
        return priority;
    }

    PowerConsumption getPowerConsumption() const
    {
        return powerConsumption;
    }

    void run() const
    {
        for (const auto &dep : dependencies)
        {
            dep->run();
        }
        execute();
    }

private:
    std::string name;
    PowerConsumption powerConsumption;
    int priority;
    std::function<void()> execute;
    std::vector<Task *> dependencies;
};

#endif // TASK_H