#pragma once

#include <filesystem>
#include <string>

namespace paths {
bool hasEnding(const std::string &fullString, const std::string &ending);
std::string findPathToCacheDirectory(const std::string &workingDirectory);
} // namespace paths
