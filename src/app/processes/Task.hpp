#ifndef TASK_HPP
#define TASK_HPP

enum class  Action {
    ENCRYPT,
    DECRYPT
};
#include<string>
#include<iostream>
#include<fstream>
#include"../fileHandling/IO.hpp"
#include<sstream>

struct Task{

    std::string filePath;
    std:: fstream f_stream;
    Action action;

    Task(std::fstream &&stream, Action act, std::string filePath)
        {
            
            f_stream = std::move(stream);
            action = act;
            filePath = filePath;
        }

        std::string toString(){
            std::ostringstream oss;
            oss<<filePath<<","<<(action ==Action::ENCRYPT? "ENCRYPT":"DECRYPT");
                // test.txt ENCRYPT    F_STREAM
            //it is called serialization, we are converting the object to a string representation         

            return oss.str();
        }


        //deserialization, we are converting the string representation back to an object
        static Task  fromString(const std::string &taskData){
            std::istringstream iss(taskData);
            std::string filePath;
            std::string actionStr;

            if(std::getline(iss, filePath, ',')&& std::getline(iss, actionStr)){
                    Action  action = (actionStr == "ENCRYPT")? Action::ENCRYPT : Action::DECRYPT;
                    IO io(filePath);
                    std::fstream f_stream = std::move(io.getFileStream());

                    if(!f_stream.is_open()){
                        std::cout << "Unable to open file: " << filePath << std::endl;
                        throw std::runtime_error("Unable to open file: " + filePath);
                    }
                    
                    return Task(std::move(f_stream), action, filePath);
            }       
        }


};

#endif // TASK_HPP