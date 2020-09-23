#pragma once

#include "client_manager.h"
#include "server.h"
#include "algorithms.hpp"
#include "exceptions.h"

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
    ClientHandler(const int &serverFd);
    /**
     * @brief talk with the client and solve his problem
     * 
     * @param client the client that the server talk with
     */
    virtual void handleClient(const client_side::Client &client) const = 0;
  };

  class TestClientHandler : ClientHandler {
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
     * @brief Construct a new Test Client Handler object
     * 
     * @param serverFd the file descriptor of the server
     */
    TestClientHandler(const int &serverFd);
    /**
     * @brief talk with the client and solve his problem
     * 
     * @param client the client that the server talk with
     */
    void handleClient(const client_side::Client &client) const;
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