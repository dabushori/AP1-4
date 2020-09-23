#include "client_manager.h"

namespace client_side {
Client::Client(int fd) : m_fd(fd) {}

int Client::inputToServer() const{
  std::string line, sendInput;
  getline(std::cin, line);
  while (line != "\r\n" ) {
    sendInput += line;
    sendInput += ";";
    getline(std::cin, line);
  }
  if (send(m_fd, sendInput.data(), sendInput.length(), 0) < 0) {
    // error
  }
  return sendInput.length();
}

std::string Client::recvMessageFromServer(const int outputLength) const{
  std::string output(outputLength, '\0');
  const auto bytesRead = recv(m_fd, output.data(), output.length() - 1, 0);
  if (bytesRead < 0) {
    // error
  }
  output[bytesRead] = '\0';
  return output;
}

int Client::getFd() const { return m_fd; }

void Client::killClient() const { close(m_fd); }
} // namespace client_side