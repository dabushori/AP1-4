#pragma once

#include "exceptions.h"

#include <filesystem>
#include <string>

namespace paths {

/**
 * @brief check if a string ends with another string
 *
 * @param fullString the full string
 * @param ending the ending
 * @return true if it is ending with the ending string
 * @return false otherwise
 */
bool hasEnding(const std::string &fullString, const std::string &ending);

/**
 * @brief a method to find the cache directory
 *
 * @param workingDirectory the current working directory
 * @return std::string the path to the cache directory
 */
std::string findPathToCacheDirectory(const std::string &workingDirectory);
} // namespace paths
