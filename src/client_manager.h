#pragma once

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace client_side {
class Client {
private:
  sockaddr m_socket;
  int m_fd;

public:
  Client(sockaddr addr, int fd);
  void inputToServer();
  std::string recvMessageFromServer();
  int getFd();
  void killClient();
};
} // namespace client_side