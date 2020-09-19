#include "client_manager.h"

namespace client_side {
Client::Client(sockaddr addr, int fd) : m_socket(addr), m_fd(fd) {}

void Client::inputToServer() {
  std::string input;
  getline(std::cin, input);
  if (send(m_fd, input.data(), input.length(), 0) < 0) {
    // error
  }
}

std::string Client::recvMessageFromServer() {}
} // namespace client_side