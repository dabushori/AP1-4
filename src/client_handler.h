#pragma once

#include "client_manager.h"

#include <iostream>

namespace server_side {
class ClientHandler {
public:
  virtual void handleClient(const client_side::Client &client,
                            const server_side::Server *server) = 0;
};

class ClientHandlerTester : public ClientHandler {
  void handleClient(const client_side::Client &client,
                    const server_side::Server *server);
};

class GraphClientHandler : public ClientHandler {
  void handleClient(const client_side::Client &client,
                    const server_side::Server *server);
};
} // namespace server_side