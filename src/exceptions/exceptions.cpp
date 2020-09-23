#include "exceptions.h"

namespace exceptions {
StatusException::StatusException(const int &status) : m_status(static_cast<Status>(status)) {}
StatusException::StatusException(const Status &status) : m_status(status) {}
int StatusException::getStatus() { return static_cast<int>(m_status); }
} // namespace exceptions