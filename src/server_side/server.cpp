#include "server.h"

namespace server_side {
void Server::open(const int port, ClientHandler *c) {
  m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_serverFd < 0) {
    throw std::system_error(errno, std::system_category());
  }
  m_addr = sockaddr_in{};
  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(port);
  if (inet_aton(IP, &m_addr.sin_addr) == 0) {
    close(m_serverFd);
    throw std::system_error(errno, std::system_category());
  }
  if (bind(m_serverFd, reinterpret_cast<sockaddr *>(&m_addr), sizeof(m_addr)) <
      0) {
    close(m_serverFd);
    throw std::system_error(errno, std::system_category());
  }
  if (listen(m_serverFd, BACKLOG_SIZE) < 0) {
    close(m_serverFd);
    throw std::system_error(errno, std::system_category());
  }
  talkWithClients(c);
}

void threadFunction(ParallelServer *server, ClientHandler *c,
                    std::mutex *mutex) {
  while (true) {
    std::unique_lock<std::mutex> ul(server->m_mutex);
    server->m_queueEmpty.wait(ul);
    std::cout << "NOTIFIED!" << std::endl;
    if (!server->m_clients.empty()) {
      client_side::Client client = server->m_clients.front();
      server->m_clients.pop();
      ul.unlock();
      std::cout << "HANDLING!" << std::endl;
      c->handleClient(client, mutex);
    }
  }
}

void ParallelServer::talkWithClients(ClientHandler *c) {
  std::thread threadPool[THREAD_POOL_SIZE];
  for (int i = 0; i < THREAD_POOL_SIZE; i++) {
    threadPool[i] = std::thread(threadFunction, this, c, &m_cacheMutex);
  }

  while (true) {
    socklen_t clientLen = 0;
    sockaddr clientAddr{};
    auto clientFd = accept(m_serverFd, &clientAddr, &clientLen);
    if (clientFd < 0) {
      close(m_serverFd);
      throw std::system_error(errno, std::system_category());
    }
    client_side::Client client(clientFd);
    m_mutex.lock();
    m_clients.push(client);
    m_mutex.unlock();
    m_queueEmpty.notify_one();
  }
  killServer();
}

void Server::killServer() const { close(m_serverFd); }

int Server::getFD() const { return m_serverFd; }

void SerialServer::talkWithClients(ClientHandler *c) {
  while (true) {
    socklen_t clientLen = 0;
    sockaddr clientAddr{};
    auto clientFd = accept(m_serverFd, &clientAddr, &clientLen);
    if (clientFd < 0) {
      close(m_serverFd);
      throw std::system_error(errno, std::system_category());
    }
    client_side::Client client(clientFd);
    c->handleClient(client, nullptr);
  }
  killServer();
}
} // namespace server_side