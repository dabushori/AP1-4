#include "server.h"

namespace server_side {
void Server::open(const int port, const ClientHandler *c) {
  m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_serverFd < 0) {
    // error
  }
  m_addr = sockaddr_in{};
  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htonl(port);
  if (bind(m_serverFd, reinterpret_cast<sockaddr *>(&m_addr), sizeof(m_addr)) <
      0) {
    close(m_serverFd);
    // error
  }
  if (listen(m_serverFd, BACKLOG_SIZE) < 0) {
    close(m_serverFd);
    // error
  }
  talkWithClients(c);
}

void ParallelServer::threadFunction(const ClientHandler *c) {
  while (true) {
    m_mutex.lock();
    m_queueEmpty.wait(m_mutex);
    if (!m_clients.empty()) {
      client_side::Client client = m_clients.front();
      m_clients.pop();
      m_mutex.unlock();
      c->handleClient(client);
    }
  }
}

void ParallelServer::talkWithClients(const ClientHandler *c) {
  std::thread threadPool[THREAD_POOL_SIZE];
  for (int i = 0; i < THREAD_POOL_SIZE; i++) {
    threadPool[i] = std::thread(threadFunction, c);
  }

  while (true) {
    socklen_t clientLen = 0;
    sockaddr clientAddr{};
    auto clientFd = accept(m_serverFd, &clientAddr, &clientLen);
    if (clientFd < 0) {
      close(m_serverFd);
      // error
    }
    client_side::Client client(clientFd);
    m_mutex.lock();
    m_queueEmpty.notify_one();
    m_clients.push(client);
    m_mutex.unlock();
  }
  killServer();
}

void Server::killServer() const { close(m_serverFd); }

void SerialServer::talkWithClients(const ClientHandler *c) {
    while (true) {
    socklen_t clientLen = 0;
    sockaddr clientAddr{};
    auto clientFd = accept(m_serverFd, &clientAddr, &clientLen);
    if (clientFd < 0) {
      close(m_serverFd);
      // error
    }
    client_side::Client client(clientFd);
    c->handleClient(client);
  }
  killServer();
}
} // namespace server_side