#include "ReadEnv.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string ReadEnv::getenv() {
    std::string env_path = ".env";
    std::ifstream f_Stream(env_path);
    if (!f_Stream.is_open()) {
        std::cerr << "Warning: Could not open .env file, using default key 0" << std::endl;
        return "0";
    }
    std::stringstream buffer;
    buffer << f_Stream.rdbuf();
    std::string content = buffer.str();
    if (content.empty()) {
        return "0";
    }
    return content;
}
