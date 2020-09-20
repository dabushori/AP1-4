#pragma once

#include "client_manager.h"


namespace server_side {
  class ClientHandler {
    public:
    virtual void handleClient(const client_side::Client) const = 0;
  };

  class TestClientHandler : ClientHandler {
    private:
      Solver m_solver;
    public:
    void handleClient(const client_side::Client) const;
  };
} // namespace server_side