#include "ProcessManagement.hpp"
#include <iostream> 
#include <cstring>
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
    return true;
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();

        // Close initial stream if still open so executeCryption / fromString can open it cleanly
        if (taskToExecute->f_stream.is_open()) {
            taskToExecute->f_stream.close();
        }

        std::cout << "Execute task : " << taskToExecute->toString() << std::endl;
        executeCryption(taskToExecute->toString());
    }
}
