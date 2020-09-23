#include "client_handler.h"
#include "server.h"

#include <iostream>
#include <regex>

int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    std::cout << "wrong args, try again" << std::endl;
    return 0;
  }
  int port = std::stoi(argv[1]);
  std::string type = argv[2];
  std::regex typeRegex("(parallel|serial)");
  if (!std::regex_match(type, typeRegex)) {
    std::cout << "wrong server type, try again" << std::endl;
    return 0;
  }

  if (type == "parallel") {
    server_side::ParallelServer server;
    server_side::GraphClientHandler handler(server.getFD());
    server.open(port, &handler);
  } else if (type == "serial") {
    server_side::SerialServer server;
    server_side::GraphClientHandler handler(server.getFD());
    server.open(port, &handler);
  }
}