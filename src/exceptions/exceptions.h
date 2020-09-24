#pragma once

#include <exception>

namespace exceptions {
enum class Status {
  success,
  noSolution,
  wrongMatrix,
  wrongInput,
  noCacheDir,
  cacheFileError,
  timeoutPassed

};

class StatusException : public std::exception {
private:
  Status m_status;

public:
  StatusException(const int &status);
  StatusException(const Status &status);
  int getStatus();
};
} // namespace exceptions