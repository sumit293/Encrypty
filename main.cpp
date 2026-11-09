#include <iostream>
#include <filesystem>
#include  "./src/app/processes/ProcessManagement.hpp"
#include"./src/app/processes/Task.hpp"
namespace fs = std::filesystem;
int main(int argc, char *argv[]){
std::string directory;
std::string action;

std::cout<<"Enter the directory path: "<<std::endl;
std::getline(std::cin, directory);

std::cout<<"Enter the action (encrypt/decrypt): "<<std::endl;
std::getline(std::cin, action);

try
{
   
if(fs::exists(directory) && fs::is_directory(directory)){
    ProcessManagement processManagement;
    for(const auto &entry: fs::recursive_directory_iterator(directory)){
        if(entry.is_regular_file()){
            std::string  filePath =  entry.path().string();
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());

            if(f_stream.is_open()){
                Action taskAction =  (action=="ENCYPT") ? Action::ENCRYPT : Action::DECRYPT;
                auto task = std::make_unique<Task>(std::move(f_stream), taskAction, filePath);
                processManagement.submitToQueue(std::move(task));
            }
            else{
                std::cout << "Unable to open file: " << filePath << std::endl;
            }
        }
    }
    processManagement.executeTasks();

}
else {
    
    std::cerr << "Invalid directory path: " << directory << std::endl;
}

}
catch(const fs::filesystem_error &e)
{
    std::cerr << "Filesystem error: " << e.what() << '\n';
}
catch(const std::exception &e)
{
    std::cerr << e.what() << '\n';
}

}




//Encrypty\src\app\process\ProcessManagement.cpp