#include "client_handler.h"

namespace server_side {
    void TestClientHandler::handleClient(const client_side::Client) const {
        m_solver.solve(); /// not clear what to do
    }
} // namespace server_side