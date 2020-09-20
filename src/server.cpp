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

  if (listen(m_serverFd, SIZE_OF_BACKLOG) < 0) {
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

void SerialServer::handleClient() { m_handler->handleClient(m_client, this); }

void SerialServer::killClient() { m_client.killClient(); }

void SerialServer::sendMessage(std::string message) {
  if (send(m_client.getFd(), message.data(), message.length(), 0) < 0) {
    close(m_client.getFd());
    // error
  }
}

std::string SerialServer::recvMessage(uint32_t len) {
  std::string message(len + 1, '\0');
  auto nBytes = read(m_client.getFd(), message.data(), len);
  if (nBytes < 0) {
    close(m_client.getFd());
    // error
  }
  message[nBytes] = '\0';
  return message;
}
} // namespace server_side