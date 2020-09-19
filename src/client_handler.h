#pragma once

#include "client_manager.h"

#include <iostream>

namespace server_side {
class ClientHandler {
public:
  virtual void handleClient(const client_side::Client &client,
                            const std::istream &input,
                            const std::ostream &output) = 0;
};

class ClientHandlerTester : public ClientHandler {
  void handleClient(const client_side::Client &client,
                    const std::istream &input, const std::ostream &output);
};

class GraphClientHandler : public ClientHandler {
  void handleClient(const client_side::Client &client,
                    const std::istream &input, const std::ostream &output);
};
} // namespace server_side