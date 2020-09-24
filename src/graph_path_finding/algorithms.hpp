#pragma once

#include "cache.h"
#include "exceptions.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <mutex>
#include <queue>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

#define PATH_NOT_FOUND "path not found";

namespace algorithms {
class GraphNode {
private:
  uint32_t m_i;
  uint32_t m_j;
  uint32_t m_iSrc;
  uint32_t m_jSrc;
  int m_cost;
  uint32_t m_dist;

public:
  /**
   * @brief Construct a new Graph Node object
   *
   */
  GraphNode();

  /**
   * @brief Construct a new Graph Node object
   *
   * @param i the row index of the node
   * @param j the col index of the node
   * @param iSrc the row index of the node source
   * @param jSrc the col index of the node source
   * @param cost the cost of the node
   */
  GraphNode(const uint32_t &i, const uint32_t &j, const uint32_t &iSrc,
            const uint32_t &jSrc, const int &cost);

  /**
   * @brief Get the RowIndex
   *
   * @return uint32_t the RowIndex
   */
  uint32_t getRowIndex() const;

  /**
   * @brief Get the ColIndex
   *
   * @return uint32_t the ColIndex
   */
  uint32_t getColIndex() const;

  /**
   * @brief Get the sourceI
   *
   * @return uint32_t the sourceI
   */
  uint32_t getSourceI() const;

  /**
   * @brief Get the sourceJ
   *
   * @return uint32_t the sourceJ
   */
  uint32_t getSourceJ() const;

  /**
   * @brief Set the Source
   *
   * @param iSrc the source's row index
   * @param jSrc the source's col index
   */
  void setSource(const uint32_t &iSrc, const uint32_t &jSrc);

  /**
   * @brief Get the Cost
   *
   * @return int the Cost
   */
  int getCost() const;

  /**
   * @brief Set the Cost
   *
   * @param cost the new Cost
   */
  void setCost(const int &cost);

  /**
   * @brief Get the Dist
   *
   * @return uint32_t the Dist
   */
  uint32_t getDist() const;

  /**
   * @brief Set the Dist
   *
   * @param dist the new Dist
   */
  void setDist(const uint32_t &dist);

  /**
   * @brief check if two nodes are equal
   *
   * @param other the other node
   * @return true if they are equal
   * @return false if they are not equal
   */
  bool operator==(const GraphNode &other) const;

  /**
   * @brief compare two nodes are not equal
   *
   * @param other the other node
   * @return true if they are not equal
   * @return false if they are equal
   */
  bool operator!=(const GraphNode &other) const;
};

class Graph {
private:
  std::vector<std::vector<GraphNode>> m_graph;
  uint32_t m_height;
  uint32_t m_width;

public:
  /**
   * @brief Construct a new Graph object
   *
   * @param graph the 2D matrix to create the graph from
   * @param height the height of the graph
   * @param width the width of the graph
   */
  Graph(std::vector<std::vector<int>> graph, uint32_t height, uint32_t width);

  /**
   * @brief get the value in the i,j cell
   *
   * @param i the row index
   * @param j the col index
   * @return GraphNode* the value in the i,j cell of the graph
   */
  GraphNode *operator()(const int &i, const int &j);

  /**
   * @brief Get the neighbors of a node
   *
   * @param current the node
   * @return std::vector<GraphNode *> vector of pointers to the neighbors
   */
  std::vector<GraphNode *> getNeighbors(GraphNode *current);
  uint32_t getHeight();
  uint32_t getWidth();
}; // namespace algorithms

template <typename DS> class Searcher {
private:
  std::vector<GraphNode> m_closed;

protected:
  DS m_opened;

public:
  /**
   * @brief Construct a new Searcher object
   *
   */
  Searcher() = default;

  /**
   * @brief Destroy the Searcher object
   *
   */
  virtual ~Searcher() = default;

  /**
   * @brief copy ctor
   *
   */
  Searcher(const Searcher &) = default;

  /**
   * @brief assignment operator
   *
   * @return Searcher& the other object
   */
  Searcher &operator=(const Searcher &) = default;

  /**
   * @brief move ctor
   *
   */
  Searcher(Searcher &&) = default;

  /**
   * @brief move assignment operator
   *
   * @return Searcher& the other object
   */
  Searcher &operator=(Searcher &&) = default;

  /**
   * @brief add a node to the opened list
   *
   * @param node the node we want to add
   */
  void addToOpened(GraphNode *node) { m_opened.push(*node); }

  /**
   * @brief remove the first node of the opened list
   *
   * @return GraphNode the node that was removed
   */
  virtual GraphNode removeFromOpened() = 0;

  /**
   * @brief check if the opened list is empty
   *
   * @return true if it is empty
   * @return false otherwise
   */
  bool isDSEmpty() { return m_opened.empty(); }

  /**
   * @brief to check if a node is in the closed list
   *
   * @param node the node
   * @return true if it is in the closed list
   * @return false otherwise
   */
  virtual bool isInClosed(GraphNode *node) {
    for (auto it = m_closed.begin(); it != m_closed.end(); ++it) {
      if (*it == *node) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief search a path in the graph using different algorithms
   *
   * @param graph the graph
   * @param start the start node
   * @param end the end node
   * @return std::vector<GraphNode> a vector of nodes that represents the path
   * (empty vector if there's no path)
   */
  virtual std::vector<GraphNode> search(Graph *graph, GraphNode *start,
                                        GraphNode *end) {
    if (start == nullptr || end == nullptr || start->getCost() == -1 ||
        end->getCost() == -1) {
      return std::vector<GraphNode>();
    }
    if (start == end || *start == *end) {
      return std::vector<GraphNode>();
    }
    addToOpened(start);
    m_closed.push_back(*start);
    while (!isDSEmpty()) {
      auto current = removeFromOpened();
      if (current == *end) {
        std::vector<GraphNode> path;
        auto *node = &current;
        while (*node != *start) {
          path.emplace(path.begin(), *node);
          node = (*graph)(node->getSourceI(), node->getSourceJ());
        }
        path.emplace(path.begin(), *node);

        std::cout << "path size of DFS: " << path.size() << std::endl;

        for (auto p : path) {
          std::cout << p.getSourceI() << "," << p.getSourceJ() << std::endl;
        }

        return path;
      }
      for (auto neighbor : graph->getNeighbors(&current)) {
        if (!isInClosed(neighbor)) {
          neighbor->setSource(current.getRowIndex(), current.getColIndex());
          addToOpened(neighbor);
          m_closed.push_back(*neighbor);
        }
      }
    }
    return std::vector<GraphNode>();
  }
};

class BestFSComperator {
public:
  /**
   * @brief compare 2 different nodes for the priority queue
   *
   * @param n1 first node
   * @param n2 second node
   * @return true if n1 'wins'
   * @return false otherwise
   */
  bool operator()(const GraphNode &n1, const GraphNode &n2);
};

class BFS : public Searcher<std::queue<GraphNode>> {
  /**
   * @brief a method to remove the first element in the queue
   *
   * @return GraphNode the element that was removed
   */
  GraphNode removeFromOpened();
};

class DFS : public Searcher<std::stack<GraphNode>> {
  /**
   * @brief a method to remove the first element in the stack
   *
   * @return GraphNode the element that was removed
   */
  GraphNode removeFromOpened();
};

class BestFS
    : public Searcher<std::priority_queue<GraphNode, std::vector<GraphNode>,
                                          BestFSComperator>> {
  /**
   * @brief a method to remove the first element in the priority queue
   *
   * @return GraphNode the element that was removed
   */
  GraphNode removeFromOpened();
}; // namespace algorithms

/**
 * @brief a method to check if an element is in the priority queue
 *
 * @tparam S first parameter for the priority queue type
 * @tparam T second parameter for the priority queue type
 * @tparam U third parameter for the priority queue type
 * @param element the element
 * @param pq the priority queue
 * @return true if the element is in the priority queue
 * @return false otherwise
 */
template <typename S, typename T, typename U>
bool isElementInPQ(S *element, std::priority_queue<S, T, U> pq) {
  while (!pq.empty()) {
    if (pq.top() == *element) {
      return true;
    }
    pq.pop();
  }
  return false;
}

class AStar {
public:
  class AStarComperator {
  public:
    /**
     * @brief compare 2 different nodes for the priority queue
     *
     * @param n1 first node
     * @param n2 second node
     * @return true if n1 'wins'
     * @return false otherwise
     */
    bool operator()(const GraphNode &n1, const GraphNode &n2);
  };

  /**
   * @brief a method to check if an element is in the data structure
   *
   * @tparam DS the data structure's type
   * @param ds the data structure
   * @param node the element
   * @return true if the element is in the data structure
   * @return false otherwise
   */
  template <typename DS> bool isInDS(DS ds, GraphNode *node) {
    return isElementInPQ<GraphNode, std::vector<GraphNode>,
                         AStar::AStarComperator>(node, ds);
  }

  /**
   * @brief remove an element from the priority queue
   *
   * @param pq the priority queue
   * @param node the element
   */
  void removeFromPQ(std::priority_queue<GraphNode, std::vector<GraphNode>,
                                        AStar::AStarComperator> *pq,
                    GraphNode *node);

  /**
   * @brief check if 2 nodes are neighbors
   *
   * @param node1 first node
   * @param node2 second node
   * @return true if they are neighbors
   * @return false otherwise
   */
  bool isNeighbors(GraphNode *node1, GraphNode *node2);

  /**
   * @brief search a path in a graph using A* algorithm
   *
   * @param graph the graph
   * @param start the start node
   * @param end the end node
   * @return std::vector<GraphNode>
   */
  std::vector<GraphNode> search(Graph *graph, GraphNode *start, GraphNode *end);

private:
  std::vector<GraphNode> m_closed;
  std::priority_queue<GraphNode, std::vector<GraphNode>, AStar::AStarComperator>
      m_nodes;
};

/**
 * @brief a method to delete spaces and tabs from a string
 *
 * @param str refernce to the string
 */
void deleteSpaces(std::string &str);

/**
 * @brief parse a vector of strings into matrix
 *
 * @param text the vector of strings
 * @return std::vector<std::vector<int>> the 2D matrix
 */
std::vector<std::vector<int>> textToMat(const std::vector<std::string> &text);

/**
 * @brief a method to parse a string into a matrix. the string is build in a
 * specific format:
 * <height>,<width>;a00,a01,...,a0n;...;an0,...,ann;<startI>,<startJ>;<<endI>,<endJ>;
 * the string parameter will become to <startI>,<startJ>;<<endI>,<endJ>
 *
 * @param matrix the string in the described format
 * @return std::vector<std::vector<int>> the 2D matrix
 */
std::vector<std::vector<int>> parseMatrix(std::string &matrix);

/**
 * @brief parse 2 nodes (source and destination) into an action - UP, DOWN, LEFT
 * or RIGHT
 *
 * @param src the source node
 * @param dest the destination node
 * @return std::string the action
 */
std::string parseNeighborsLocation(const GraphNode &src, const GraphNode &dest);

/**
 * @brief search path in a graph using a given algorithm and a cache
 *
 * @param algorithm the algorithm (DFS, BFS, BestFS or A*)
 * @param matrix the matrix in the format mentioned above
 * @return std::string the result string in the format:
 * <path cost>,<algorithm>,<action 1>,...,<action n>
 */
std::string searchInGraph(std::string algorithm, std::string matrix,
                          std::mutex *mutex);
} // namespace algorithms