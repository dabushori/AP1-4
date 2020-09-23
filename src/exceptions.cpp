#include "exceptions.h"

namespace exceptions {
StatusException::StatusException(Status status) : m_status(status) {}
int StatusException::getStatus() { return static_cast<int>(m_status); }
} // namespace exceptions