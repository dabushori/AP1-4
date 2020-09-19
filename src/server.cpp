#include "server.h"

namespace server_side {
void SerialServer::open(int port, const ClientHandler &handler) {
  *m_handler = handler;

  m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_serverFd <= 0) {
    // error
  }

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htonl(port);
  if (inet_aton(IP, &addr.sin_addr) == 0) {
    close(m_serverFd);
    // error
  }

  if (bind(m_serverFd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
    close(m_serverFd);
    // error
  }

  if (listen(m_serverFd, NUM_OF_CLIENTS) < 0) {
    close(m_serverFd);
    // error
  }
}

void SerialServer::kill() { close(m_serverFd); }

void SerialServer::connectClient() {
  socklen_t clientLen = 0;
  sockaddr clientAddr{};
  auto clientFd = accept(m_serverFd, &clientAddr, &clientLen);
  if (clientFd < 0) {
    close(m_serverFd);
    // error
  }
  m_client = client_side::Client(clientAddr, clientFd);
}

void SerialServer::handleClient() {
  m_handler->handleClient(m_client, std::cin, std::cout);
}

void SerialServer::sendMessage(std::string message) {}

std::string SerialServer::recvMessage() {}

void ParallelServer::open(int port, const ClientHandler &handler) {}

void ParallelServer::kill() {}
} // namespace server_side