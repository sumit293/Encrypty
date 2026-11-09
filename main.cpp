#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    std::string directory;
    std::string action;

    std::cout << "Enter the directory or file path: " << std::endl;
    std::getline(std::cin, directory);

    // Strip optional surrounding quotes from path (common when copying paths on Windows)
    if (directory.size() >= 2 && ((directory.front() == '"' && directory.back() == '"') || 
                                  (directory.front() == '\'' && directory.back() == '\''))) {
        directory = directory.substr(1, directory.size() - 2);
    }

    std::cout << "Enter the action (encrypt/decrypt): " << std::endl;
    std::getline(std::cin, action);

    std::string actionUpper = action;
    for (char &c : actionUpper) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    if (actionUpper != "ENCRYPT" && actionUpper != "ENCYPT" && actionUpper != "DECRYPT") {
        std::cerr << "Invalid action: " << action << ". Please enter 'encrypt' or 'decrypt'." << std::endl;
        return 1;
    }

    Action taskAction = (actionUpper == "ENCRYPT" || actionUpper == "ENCYPT") ? Action::ENCRYPT : Action::DECRYPT;

    try {
        if (fs::exists(directory)) {
            ProcessManagement processManagement;

            auto queueFile = [&](const std::string &filePath) {
                IO io(filePath);
                std::fstream f_stream = io.getFileStream();

                if (f_stream.is_open()) {
                    auto task = std::make_unique<Task>(std::move(f_stream), taskAction, filePath);
                    processManagement.submitToQueue(std::move(task));
                } else {
                    std::cout << "Unable to open file: " << filePath << std::endl;
                }
            };

            if (fs::is_directory(directory)) {
                for (const auto &entry : fs::recursive_directory_iterator(directory)) {
                    if (entry.is_regular_file()) {
                        queueFile(entry.path().string());
                    }
                }
            } else if (fs::is_regular_file(directory)) {
                queueFile(directory);
            }

            processManagement.executeTasks();
        } else {
            std::cerr << "Invalid directory or file path: " << directory << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
