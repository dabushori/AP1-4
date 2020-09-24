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
/**
 * @brief Construct a new Status Exception object
 * 
 * @param status the status
 */
  StatusException(const int &status);

  /**
   * @brief Construct a new Status Exception object
   * 
   * @param status the status
   */
  StatusException(const Status &status);

  /**
   * @brief Get the Status 
   * 
   * @return int the status
   */
  int getStatus();
};
} // namespace exceptions