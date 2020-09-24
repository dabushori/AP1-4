#pragma once

#include "exceptions.h"
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
  /**
   * @brief Construct a new Cache object
   *
   */
  Cache();

  /**
   * @brief save a solution for a problem in the cache
   *
   * @param algorithm the algorithm of the solution
   * @param problem the problem
   * @param solution the solution
   */
  void save(const std::string &algorithm, const std::string &problem,
            const std::string &solution);

  /**
   * @brief look for the solution to a given problem in the cache
   *
   * @param alorithm the algorithm
   * @param problem the problem
   * @return std::string the result (an empty string if it doesn't in the cache)
   */
  std::string searchSolutionFor(const std::string &alorithm,
                                const std::string &problem);

  /**
   * @brief a method to clear the cache
   *
   */
  void clear();
};
} // namespace cache