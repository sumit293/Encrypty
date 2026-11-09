#include"Cryption.hpp"
#include"../process/Task.hpp"
#include"../fileHandling/ReadEnv.cpp"

int executeCryption (const std::string &taskData){
    Task task  = Task::fromString (taskData);
    ReadEnv env;

    std::string envKey = env.getenv();
    int key = std::stoi(envKey);

    if (task.action == Action::ENCRYPT){
        char ch;
         while(task.f_stream.get(ch)){
            ch = (ch + key) % 256; // simple encryption by shifting ASCII value
            task.f_stream.seekp(-1, std::ios::cur); // move the put pointer back to overwrite the character
            task.f_stream.put(ch);
         }

         task.f_stream.close();
        
    }

    else {
        char ch ;
          while(task.f_stream.get(ch)){
            ch  = (ch-key+256) % 256; // simple decryption by shifting ASCII value back
            task.f_stream.seekp(-1, std::ios::cur); // move the put pointer back to overwrite the character
            task.f_stream.put(ch);  
          }

          task.f_stream.close();

    }
    return 0;
    
}