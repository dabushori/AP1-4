#pragma once

#include <exception>

namespace exceptions {
enum class Status { success, noSolution, wrongMatrix, wrongInput };

class StatusException : public std::exception {
private:
  Status m_status;

public:
  StatusException(Status status);
  int getStatus();
};
} // namespace exceptions