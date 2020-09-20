#include "server.h"

namespace server_side {
    void SerialServer::open(const int port, const ClientHandler *c){
        m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_serverFd < 0) {
            //error
        }
        m_addr = sockaddr_in{};
        m_addr.sin_family = AF_INET;
        m_addr.sin_addr.s_addr = INADDR_ANY;
        m_addr.sin_port = htonl(port);
        if(bind(m_serverFd, reinterpret_cast<sockaddr*>(&m_addr), sizeof(m_addr)) < 0) {
            close(m_serverFd);
            //error
        }
        if (listen(m_serverFd, BACKLOG_SIZE) < 0) {
            close(m_serverFd);
            //error
        }
        talkWithClients(c);
    }

    void SerialServer::handleTheClient(const ClientHandler *c, const client_side::Client &client) const {
        c->handleClient(client);
    }

    void SerialServer::talkWithClients(const ClientHandler *c) const {
        std::thread threadPool[THREAD_POOL_SIZE]; //hereeeeeeeee      
        while (true) {
            const auto addrSize = sizeof(sockaddr);
            socklen_t clientLen = 0;
            sockaddr clientAddr{};
            auto clientFd = accept(m_serverFd, &clientAddr, &clientLen);
            if (clientFd < 0) {
                close(m_serverFd);
                //error
            }
            client_side::Client client(clientAddr, clientFd);
            handleTheClient(c, client);

            std::thread thread(handleTheClient, c, client);
        }
        killServer();
    }

    void SerialServer::killServer() const {

    }
} // namespace server_side