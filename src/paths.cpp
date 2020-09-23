#include "paths.h"

namespace paths {
bool hasEnding(const std::string &fullString, const std::string &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare(fullString.length() - ending.length(),
                                    ending.length(), ending));
  }
  return false;
}

std::string findPathToCacheDirectory(const std::string &workingDirectory) {
  for (auto &p :
       std::filesystem::recursive_directory_iterator(workingDirectory)) {
    std::string path = p.path();
    if (hasEnding(path, "src/bin/cache")) {
      return path;
    }
  }
  return "error";
}
} // namespace paths