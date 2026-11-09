#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "../fileHandling/IO.hpp"

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::string filePath;
    std::fstream f_stream;
    Action action;

    Task(std::fstream &&stream, Action act, std::string fPath)
        : filePath(std::move(fPath)), f_stream(std::move(stream)), action(act) {
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    static Task fromString(const std::string &taskData) {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
            Action action = (actionStr == "ENCRYPT") ? Action::ENCRYPT : Action::DECRYPT;
            IO io(filePath);
            std::fstream f_stream = io.getFileStream();

            if (!f_stream.is_open()) {
                std::cout << "Unable to open file: " << filePath << std::endl;
                throw std::runtime_error("Unable to open file: " + filePath);
            }
            
            return Task(std::move(f_stream), action, filePath);
        }
        throw std::runtime_error("Invalid task data format: " + taskData);
    }
};

#endif // TASK_HPP
