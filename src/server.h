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

constexpr auto IP = "127.0.0.1";
constexpr auto SIZE_OF_BACKLOG = 3;
constexpr auto DEFAULT_ALGORITHM = "A*";
constexpr auto CLIENT_FIRST_INPUT = "solve path-graph-find";
constexpr auto CLIENT_FIRST_INPUT_LEN = 21;

namespace server_side {
class Server {
public:
  virtual void open(int port, const ClientHandler &handler) = 0;
  virtual void kill() = 0;
  virtual void connectClient() = 0;
  virtual void handleClient() = 0;
  virtual void sendMessage(std::string message) = 0;
  virtual std::string recvMessage(uint32_t len) = 0;
};

class SerialServer : public Server {
private:
  sockaddr m_server;
  int m_serverFd;
  client_side::Client m_client;
  std::unique_ptr<ClientHandler> m_handler;

public:
  void open(int port, const ClientHandler &handler);
  void kill();
  void connectClient();
  void handleClient();
  void killClient();
  void sendMessage(std::string message);
  std::string recvMessage(uint32_t len);
};

class ParallelServer : public Server {
private:
  std::vector<sockaddr> m_sockets;

public:
  void open(int port, const ClientHandler &handler);
  void kill();
};
} // namespace server_side