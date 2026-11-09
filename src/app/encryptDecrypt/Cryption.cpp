#include "Cryption.hpp"
#include "../fileHandling/ReadEnv.hpp"
#include "../processes/Task.hpp"
#include <iostream>

int executeCryption(const std::string &taskData) {
  Task task = Task::fromString(taskData);
  ReadEnv env;

  std::string envKey = env.getenv();
  int key = ((std::stoi(envKey) % 256) + 256) % 256;

  if (task.action == Action::ENCRYPT) {
    char ch;
    while (task.f_stream.get(ch)) {
      unsigned char uch = static_cast<unsigned char>(ch);
      uch = (uch + key) % 256;
      task.f_stream.seekp(-1, std::ios::cur);
      task.f_stream.put(static_cast<char>(uch));
      task.f_stream.flush();
    }
    task.f_stream.close();
  } else {
    char ch;
    while (task.f_stream.get(ch)) {
      unsigned char uch = static_cast<unsigned char>(ch);
      uch = (uch - key + 256) % 256;
      task.f_stream.seekp(-1, std::ios::cur);
      task.f_stream.put(static_cast<char>(uch));
      task.f_stream.flush();
    }
    task.f_stream.close();
  }
  return 0;
}
