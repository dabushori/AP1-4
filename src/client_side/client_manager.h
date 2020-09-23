#pragma once

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace client_side {
class Client {
private:
  sockaddr m_socket;
  int m_fd;

public:
/**
 * @brief Construct a new Client object
 * 
 * @param fd the file descriptor of the client.
 */
  Client(int fd);
  /**
   * @brief sends to the server everything that the client write.
   * 
   * @return int - length of the message that the client sent. 
   */
  int inputToServer() const;
  /**
   * @brief the function recieve a message from the server and return it.
   * 
   * @param outputLength the length of the message
   * @return std::string - the message
   */
  std::string recvMessageFromServer(const int outputLength) const;
  /**
   * @brief Get the Fd object
   * 
   * @return int - fd of the client
   */
  int getFd() const;
  /**
   * @brief close the fd of the client
   * 
   */
  void killClient() const;
};
} // namespace client_side