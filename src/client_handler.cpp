#include "client_handler.h"

namespace server_side {

ClientHandler::ClientHandler(const int serverFd) : m_serverFd(serverFd) {}

TestClientHandler::TestClientHandler(const int serverFd) : ClientHandler(serverFd) {}

std::string TestClientHandler::recvMessageFromClient(const int outputLength) const {
  std::string output(outputLength, '\0');
  const auto bytesRead = recv(m_serverFd, output.data(), output.length() - 1, 0);
  if (bytesRead < 0) {
    // error
  }
  output[bytesRead] = '\0';
  return output;
}

void TestClientHandler::handleClient(const client_side::Client &client) const{
  int commandLength = client.inputToServer();
  std::string command = recvMessageFromClient(commandLength), msg = "error";
  if (command.substr(0, CLIENT_FIRST_INPUT_LEN) != CLIENT_FIRST_INPUT) {
    msg = "Can't run the command: not the correct params";
    send(m_serverFd, msg.data(), msg.length(), 0);
    client.killClient();
    return;
  }
  std::string algo = command.substr(CLIENT_FIRST_INPUT_LEN + 1);
  algo.erase(remove_if(algo.begin(), algo.end(), isspace), algo.end());
  if (algo.empty() || algo == "A*") {
    std::string defAlgo = DEFAULT_ALGORITHM;
    msg = "Success: the algorithm is " + defAlgo;
  }
  std::regex algoCheck("BestFS|BFS|DFS");
  if (std::regex_search(algo, algoCheck)) {
    msg = "Success: the algorithm is " + algo;
  }
  if (msg == "error") {
    // error
  }
  send(m_serverFd, msg.data(), msg.length(), 0);
  client.recvMessageFromServer(msg.length());
  int matrixLength = client.inputToServer();
  std::string matrix = recvMessageFromClient(matrixLength);
}
} // namespace server_side