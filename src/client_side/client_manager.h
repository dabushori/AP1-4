#pragma once

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace client_side {
class Client {
private:
  int m_fd;

public:
  /**
   * @brief Construct a new Client object
   *
   * @param fd the file descriptor of the client.
   */
  Client(const int &fd);
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