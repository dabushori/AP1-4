#pragma once

#include "client_handler.h"
#include "client_manager.h"

#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include <algorithm>
#include <arpa/inet.h>
#include <errno.h>
#include <mutex>
#include <queue>
#include <sys/socket.h>
#include <sys/types.h>
#include <system_error>
#include <thread>
#include <unistd.h>

constexpr auto IP = "127.0.0.1";
constexpr auto BACKLOG_SIZE = 30;
constexpr auto THREAD_POOL_SIZE = 5;
constexpr auto DEFAULT_ALGORITHM = "A*";
constexpr auto CLIENT_FIRST_INPUT = "solve path-graph-find";
constexpr auto CLIENT_FIRST_INPUT_LEN = 21;

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
  virtual void open(const int port,const ClientHandler *c);
  /**
   * @brief connect the server to clients and solve their problems
   *
   * @param c a ClientHandler pointer that deal with a client
   */
  virtual void talkWithClients(const ClientHandler *c) = 0;
  /**
   * @brief close the server.
   *
   */
  virtual void killServer() const;
  // no use just for the rule of 5
  virtual ~Server() = default;
  Server(const Server &) = default;
  Server &operator=(const Server &) = default;
  Server(Server &&) = default;
  Server &operator=(Server &&) = default;
};

class ParallelServer : public Server {
private:
  std::queue<client_side::Client> m_clients;
  std::unique_lock<std::mutex> m_mutex;
  std::condition_variable m_queueEmpty;

public:
  /**
   * @brief the function is used inorder to use the same threads
   * int the thread pool.
   *
   * @param c a clientHandler pointer that deal with a client
   */
  void threadFunction(const ClientHandler *c);
  /**
   * @brief connect the server to one client at a time and solve his problem.
   *
   * @param c a ClientHandler pointer that deal with a client
   */
  void talkWithClients(const ClientHandler *c);
};

class SerialServer : public Server {
public:
  /**
   * @brief connect the server to multiply clients at once and solve their
   * problems
   *
   * @param c a ClientHandler pointer that deal with a client
   */
  void talkWithClients(const ClientHandler *c);
};
} // namespace server_side