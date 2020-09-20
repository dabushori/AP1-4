#include "client_handler.h"

namespace server_side {
void ClientHandlerTester::handleClient(const client_side::Client &client,
                                       const server_side::Server *server) {}

void GraphClientHandler::handleClient(const client_side::Client &client,
                                      const server_side::Server *server) {

  // TODO change this method

  std::string buffer(1024, '\0');
  auto bytesRead = recv(m_clientFd, buffer.data(), buffer.length() - 1, 0);
  if (bytesRead < 0) {
    close(m_clientFd);
    close(m_serverFd);
    // error
  }
  buffer[bytesRead] = '\0';

  // to check buffer - solve <problem> [<alg>]
  std::regex clientMessage{"solve path-graph-find (A*|BestFS|BFS|DFS)?"};
  if (!std::regex_match(buffer.data(), clientMessage)) {
    // error
  }

  std::string algo;
  if (buffer == "solve path-graph-find") {
    algo = DEFAULT_ALGORITHM;
  } else {
    algo = buffer.substr(CLIENT_FIRST_INPUT_LEN + 1);
  }
}
} // namespace server_side