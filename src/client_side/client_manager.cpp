#include "client_manager.h"

namespace client_side {
Client::Client(int fd) : m_fd(fd) {}

int Client::getFd() const { return m_fd; }

void Client::killClient() const { close(m_fd); }
} // namespace client_side