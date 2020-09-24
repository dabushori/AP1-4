#pragma once

#include "algorithms.hpp"
#include "client_manager.h"
#include "exceptions.h"

#include <regex>

constexpr auto DEFAULT_ALGORITHM = "A*";
constexpr auto CLIENT_FIRST_INPUT = "solve find-graph-path";
constexpr auto CLIENT_FIRST_INPUT_LEN = 21;
constexpr auto ALGO_MAX_LEN = 6;

namespace server_side {
class ClientHandler {
protected:
  int m_serverFd;
  /**
   * @brief recieve a message from the client.
   *
   * @param outputLength - length of the message
   * @return std::string - the message
   */
  virtual std::string recvMessageFromClient(const int &outputLength) const = 0;

public:
  /**
   * @brief Construct a new Client Handler object
   *
   * @param serverFd the file descriptor of the server
   */
  ClientHandler();
  /**
   * @brief talk with the client and solve his problem
   *
   * @param client the client that the server talk with
   */
  virtual void handleClient(const client_side::Client &client,
                            std::mutex *mutex) = 0;

  virtual ~ClientHandler() = default;
  ClientHandler(const ClientHandler &) = default;
  ClientHandler &operator=(const ClientHandler &) = default;
  ClientHandler(ClientHandler &&) = default;
  ClientHandler &operator=(ClientHandler &&) = default;
};

class GraphClientHandler : public ClientHandler {
protected:
  /**
   * @brief recieve a message from the client.
   *
   * @param outputLength - length of the message
   * @return std::string - the message
   */
  std::string recvMessageFromClient(const int &outputLength) const;

public:
  /**
   * @brief Construct a new Graph Client Handler object
   *
   * @param serverFd the file descriptor of the server
   */
  GraphClientHandler();
  /**
   * @brief talk with the client and solve his problem
   *
   * @param client the client that the server talk with
   */
  void handleClient(const client_side::Client &client, std::mutex *mutex);
  /**
   * @brief
   *
   * @param answer
   * @param status
   * @return std::string
   */
  std::string formatAnswer(const std::string &answer, const int &status) const;
};
} // namespace server_side