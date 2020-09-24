#pragma once

#include "client_handler.h"
#include "client_manager.h"

#include <algorithm>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <system_error>
#include <thread>
#include <unistd.h>
#include <vector>

constexpr auto IP = "127.0.0.1";
constexpr auto BACKLOG_SIZE = 30;
constexpr auto THREAD_POOL_SIZE = 5;

namespace server_side {
class Server {
protected:
  int m_serverFd;
  sockaddr_in m_addr;

public:
  /**
   * @brief open the server with the current port.
   *
   * @param port the port of the server
   * @param c a ClientHandle pointer that deal with a client
   */
  virtual void open(const int &port, ClientHandler *c);
  /**
   * @brief connect the server to clients and solve their problems
   *
   * @param c a ClientHandler pointer that deal with a client
   */
  virtual void talkWithClients(ClientHandler *c) = 0;
  /**
   * @brief close the server.
   *
   */
  virtual void killServer() const;
  /**
   * @brief get the FD of the server
   *
   * @return int the FD of the server
   */
  int getFD() const;
  /**
   * @brief Construct a new Server object
   *
   */
  Server() = default;
  // no use just for the rule of 5
  virtual ~Server() = default;
  Server(const Server &) = default;
  Server &operator=(const Server &) = default;
  Server(Server &&) = default;
  Server &operator=(Server &&) = default;
};

class ParallelServer : public Server {
  friend void threadFunction(ParallelServer *server, ClientHandler *c,
                             std::mutex *mutex);

private:
  std::queue<client_side::Client> m_clients;
  std::mutex m_mutex;
  std::mutex m_cacheMutex;
  std::condition_variable m_queueEmpty;

public:
  /**
   * @brief connect the server to one client at a time and solve his problem.
   *
   * @param c a ClientHandler pointer that deal with a client
   */
  void talkWithClients(ClientHandler *c);
};

/**
 * @brief the function is used inorder to use the same threads
 * int the thread pool.
 *
 * @param c a clientHandler pointer that deal with a client
 * @param mutex a mutex to deal with the cache file
 */
void threadFunction(ParallelServer *server, ClientHandler *c,
                    std::mutex *mutex);

class SerialServer : public Server {
public:
  /**
   * @brief connect the server to multiply clients at once and solve their
   * problems
   *
   * @param c a ClientHandler pointer that deal with a client
   */
  void talkWithClients(ClientHandler *c);

  /**
   * @brief Construct a new Serial Server object
   *
   */
  SerialServer() = default;
};
} // namespace server_side