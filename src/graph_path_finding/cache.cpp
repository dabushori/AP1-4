#include "cache.h"

namespace cache {
Cache::Cache()
    : m_cacheFile(paths::findPathToCacheDirectory(
                      std::filesystem::current_path().c_str()) +
                  "/" + CACHE_FILE_NAME) {
  if (!std::filesystem::exists(m_cacheFile)) {
    std::ofstream cache(m_cacheFile, std::ios::trunc);
    cache.close();
  }
}

void Cache::save(const std::string &algorithm, const std::string &problem,
                 const std::string &solution) {
  std::ofstream cacheOut(m_cacheFile, std::ios::app);
  if (!cacheOut) {
    throw exceptions::StatusException(exceptions::Status::cacheFileError);
  }
  cacheOut << algorithm << ";" << problem << std::endl;
  cacheOut << solution << std::endl;
  cacheOut.close();
}

std::string Cache::searchSolutionFor(const std::string &algorithm,
                                     const std::string &problem) {
  std::ifstream cacheIn(m_cacheFile);
  if (!cacheIn) {
    throw exceptions::StatusException(exceptions::Status::cacheFileError);
  }
  std::string searched = algorithm + ";" + problem;
  std::string currentLine;
  while (!cacheIn.eof()) {
    getline(cacheIn, currentLine);
    if (currentLine == searched) {
      getline(cacheIn, currentLine);
      return currentLine;
    } else {
      getline(cacheIn, currentLine);
    }
  }
  return "";
}

void Cache::clear() {
  std::filesystem::remove_all(
      paths::findPathToCacheDirectory(std::filesystem::current_path().c_str()));
}

} // namespace cache