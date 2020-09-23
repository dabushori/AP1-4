#pragma once

#include "paths.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace cache {

constexpr auto CACHE_FILE_NAME = "cache.txt";

class Cache {
private:
  std::string m_cacheFile;

public:
  Cache();
  void save(std::string algorithm, std::string problem, std::string solution);
  std::string searchSolutionFor(std::string alorithm, std::string problem);
  void clear();
};
} // namespace cache