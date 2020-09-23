#pragma once

#include "cache.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
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
  GraphNode();
  GraphNode(const uint32_t &i, const uint32_t &j, const uint32_t &iSrc,
            const uint32_t &jSrc, const int &cost);
  uint32_t getRowIndex() const;
  uint32_t getColIndex() const;
  uint32_t getSourceI() const;
  uint32_t getSourceJ() const;
  void setSource(const uint32_t &iSrc, const uint32_t &m_jSrc);
  int getCost() const;
  void setCost(const int &cost);
  uint32_t getDist() const;
  void setDist(const uint32_t &dist);
  bool operator==(const GraphNode &other) const;
  bool operator!=(const GraphNode &other) const;
};

class Graph {
private:
  std::vector<std::vector<GraphNode>> m_graph;
  uint32_t m_height;
  uint32_t m_width;

public:
  Graph(std::vector<std::vector<int>> graph, uint32_t height, uint32_t width);
  GraphNode *operator()(const int &i, const int &j);
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
  void addToOpened(GraphNode *node) { m_opened.push(*node); }
  virtual GraphNode removeFromOpened() = 0;
  bool isDSEmpty() { return m_opened.empty(); }
  virtual bool isInClosed(GraphNode *node) {
    for (auto it = m_closed.begin(); it != m_closed.end(); ++it) {
      if (*it == *node) {
        return true;
      }
    }
    return false;
  }
  uint32_t findInClosed(const GraphNode &current) {
    int i = 0;
    for (auto it = m_closed.begin(); it != m_closed.end(); ++it, ++i) {
      if (*it == current) {
        return i;
      }
    }
    return -1;
  }
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
  bool operator()(const GraphNode &n1, const GraphNode &n2);
};

class BFS : public Searcher<std::queue<GraphNode>> {
  GraphNode removeFromOpened();
};

class DFS : public Searcher<std::stack<GraphNode>> {
  GraphNode removeFromOpened();
};

class BestFS
    : public Searcher<std::priority_queue<GraphNode, std::vector<GraphNode>,
                                          BestFSComperator>> {
  GraphNode removeFromOpened();
}; // namespace algorithms

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
    bool operator()(const GraphNode &n1, const GraphNode &n2);
  };
  template <typename DS> bool isInDS(DS ds, GraphNode *node) {
    return isElementInPQ<GraphNode, std::vector<GraphNode>,
                         AStar::AStarComperator>(node, ds);
  }
  void removeFromPQ(std::priority_queue<GraphNode, std::vector<GraphNode>,
                                        AStar::AStarComperator> *pq,
                    GraphNode *node);
  void updateDist(GraphNode *node, const int &newDist, Graph *g);
  void updateCost(GraphNode *node, const uint32_t &newCost, Graph *g);
  void updateSource(GraphNode *node, const uint32_t &src, Graph *g);
  uint32_t findInClosed(const GraphNode &current);
  bool isNeighbors(GraphNode *node1, GraphNode *node2);
  std::vector<GraphNode> search(Graph *graph, GraphNode *start, GraphNode *end);

private:
  std::vector<GraphNode> m_closed;
  std::priority_queue<GraphNode, std::vector<GraphNode>, AStar::AStarComperator>
      m_nodes;
};

void deleteSpaces(std::string &str);
std::vector<std::vector<int>> textToMat(const std::vector<std::string> &text);
std::vector<std::vector<int>> parseMatrix(std::string &matrix);
std::string parseNeighborsLocation(const GraphNode &src, const GraphNode &dest);
std::string searchInGraph(std::string algorithm, std::string matrix);
} // namespace algorithms