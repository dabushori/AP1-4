#pragma once

#include "client_handler.h"

#include "client_manager.h"

#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <system_error>
#include <unistd.h>
#include <thread>
#include <queue>


constexpr auto IP = "127.0.0.1";
constexpr auto BACKLOG_SIZE = 30;
constexpr auto THREAD_POOL_SIZE = 5;
constexpr auto DEFAULT_ALGORITHM = "A*";
constexpr auto CLIENT_FIRST_INPUT = "solve path-graph-find";
constexpr auto CLIENT_FIRST_INPUT_LEN = 21;

namespace server_side {
class Server {
public:
  virtual void open(const int port, const ClientHandler *c) = 0;
  virtual void handleTheClient(const ClientHandler *c, const client_side::Client &client) const =0;
  virtual void talkWithClients(const ClientHandler *c) const = 0;
  virtual void killServer() const = 0;
};

class SerialServer : public Server {
private:
  int m_serverFd;
  sockaddr_in m_addr;

public:
  void open(const int port, const ClientHandler *c);
  void handleTheClient(const ClientHandler *c, const client_side::Client &client) const;
  void talkWithClients(const ClientHandler *c) const;
  void killServer() const;
};
} // namespace server_side