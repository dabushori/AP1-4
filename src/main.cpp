#include "server.h"

#include <iostream>
#include <regex>
#include <string>

constexpr auto PARALLEL_SERVER_TYPE = "parallel";
constexpr auto SERIAL_SERVER_TYPE = "serial";
constexpr auto DEFAULT_SERVER_TYPE = PARALLEL_SERVER_TYPE;

bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), std::isdigit);
}

int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    // error
  }
  std::string port{argv[1]};
  if (!isNumber(port)) {
    // error
  }

  std::string serverType;
  if (argv == 2) {
    serverType = DEFAULT_SERVER_TYPE;
  } else {
    std::regex types = "(parallel|serial)";
    serverType = argv[2];
    if (!std::regex_match(serverType, types)) {
      // error
    }
  }

  if (serverType == SERIAL_SERVER_TYPE) {
    server_side::SerialServer server;
    server.open(std::to_integer(port), server_side::GraphClientHandler());
    while (true) {
      server.connectClient();
      server.handleClient();
      server.killClient();
    }
    server.kill();
  } else if (serverType == PARALLEL_SERVER_TYPE) {

  } else {
    // error
  }
}