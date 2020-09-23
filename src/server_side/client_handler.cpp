#include "client_handler.h"

namespace server_side {

ClientHandler::ClientHandler(const int &serverFd) : m_serverFd(serverFd) {}

TestClientHandler::TestClientHandler(const int &serverFd)
    : ClientHandler(serverFd) {}

std::string
TestClientHandler::recvMessageFromClient(const int &outputLength) const {
  std::string output(outputLength, '\0');
  const auto bytesRead =
      recv(m_serverFd, output.data(), output.length() - 1, 0);
  if (bytesRead < 0) {
    // error
  }
  output[bytesRead] = '\0';
  return output;
}

std::string TestClientHandler::formatAnswer(const std::string &answer,
                                            const int &status) const {
  std::string format = "Version: 1.0\r\nStatus: ";
  format += std::to_string(status);
  format += "\r\n";
  format += "response-length: ";
  format += std::to_string(answer.length());
  format += "\r\n";
  format += answer;
  format += "\r\n";
  return format;
}
void TestClientHandler::handleClient(const client_side::Client &client) const {
  int commandLength = client.inputToServer();
  std::string command = recvMessageFromClient(commandLength), msg = "";
  int status = static_cast<int>(exceptions::Status::success);
  std::string algo = command.substr(CLIENT_FIRST_INPUT_LEN + 1);
  try {
    if (command.substr(0, CLIENT_FIRST_INPUT_LEN) != CLIENT_FIRST_INPUT) {
      throw exceptions::StatusException(exceptions::Status::wrongInput);
    }
    algo.erase(remove_if(algo.begin(), algo.end(), isspace), algo.end());
    std::regex algoCheck("BestFS|BFS|DFS");
    if (algo.empty() || algo == "A*") {
      algo = DEFAULT_ALGORITHM;
    } else if (!std::regex_search(algo, algoCheck)) {
      throw exceptions::StatusException(exceptions::Status::wrongInput);
    }
  } catch (exceptions::StatusException &e) {
    status = e.getStatus();
    std::string firstAnswer = formatAnswer(msg, status);
    send(m_serverFd, firstAnswer.data(), firstAnswer.length(), 0);
    client.killClient();
    return;
  }
  std::string firstAnswer = formatAnswer(msg, status);
  send(m_serverFd, firstAnswer.data(), firstAnswer.length(), 0);
  std::string result = "";
  try {
  client.recvMessageFromServer(msg.length());
  int matrixLength = client.inputToServer();
  std::string matrix = recvMessageFromClient(matrixLength);
  result = algorithms::searchInGraph(algo, matrix);
  }
  catch (exceptions::StatusException &e) {
    status = e.getStatus();
    std::string finalAnswer = formatAnswer(result, status);
    send(m_serverFd, finalAnswer.data(), finalAnswer.length(), 0);
    client.killClient();
    return;
  }
  std::string finalAnswer = formatAnswer(result, status);
  send(m_serverFd, finalAnswer.data(), finalAnswer.length(), 0);
  client.killClient();
}
} // namespace server_side