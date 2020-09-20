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

std::string Client::recvMessageFromServer() {
  std::string output(1024,  '\0');
  const auto bytesRead = recv(m_fd, output.data(), output.length() - 1);
  if (bytesRead < 0) {
    // error
  }
  output[bytesRead] = '\0';
  return output;
}
} // namespace client_side