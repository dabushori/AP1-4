#include "algorithms.hpp"

namespace algorithms {
GraphNode::GraphNode()
    : m_i(0), m_j(0), m_iSrc(0), m_jSrc(0), m_cost(0), m_dist(0) {}
GraphNode::GraphNode(const uint32_t &i, const uint32_t &j, const uint32_t &iSrc,
                     const uint32_t &jSrc, const int &cost)
    : m_i(i), m_j(j), m_iSrc(iSrc), m_jSrc(jSrc), m_cost(cost), m_dist(0) {}
uint32_t GraphNode::getRowIndex() const { return m_i; }
uint32_t GraphNode::getColIndex() const { return m_j; }
uint32_t GraphNode::getSourceI() const { return m_iSrc; }
uint32_t GraphNode::getSourceJ() const { return m_jSrc; }
void GraphNode::setSource(const uint32_t &iSrc, const uint32_t &jSrc) {
  m_iSrc = iSrc;
  m_jSrc = jSrc;
}
int GraphNode::getCost() const { return m_cost; }
void GraphNode::setCost(const int &cost) { m_cost = cost; }
uint32_t GraphNode::getDist() const { return m_dist; }
void GraphNode::setDist(const uint32_t &dist) { m_dist = dist; }
bool GraphNode::operator==(const GraphNode &other) const {
  return (m_i == other.m_i) && (m_j == other.m_j);
}
bool GraphNode::operator!=(const GraphNode &other) const {
  return (m_i != other.m_i) || (m_j != other.m_j);
}
Graph::Graph(std::vector<std::vector<int>> graph, uint32_t height,
             uint32_t width) {
  std::vector<std::vector<GraphNode>> nodes;
  for (uint32_t i = 0; i < height; ++i) {
    std::vector<GraphNode> line;
    for (uint32_t j = 0; j < width; ++j) {
      line.push_back(GraphNode(i, j, 0, 0, graph[i][j]));
    }
    nodes.push_back(line);
  }
  m_height = height;
  m_width = width;
  m_graph = nodes;
}
GraphNode *Graph::operator()(const int &i, const int &j) {
  if (0 <= i && i < static_cast<int>(m_height) && 0 <= j &&
      j < static_cast<int>(m_width)) {
    return &(m_graph[i][j]);
  }
  return nullptr;
}
std::vector<GraphNode *> Graph::getNeighbors(GraphNode *current) {
  std::vector<GraphNode *> neighbors;
  auto i = current->getRowIndex(), j = current->getColIndex();
  GraphNode *curr;
  curr = (*this)(i - 1, j);
  if (curr != nullptr && curr->getCost() != -1) {
    neighbors.push_back(curr);
  }
  curr = (*this)(i + 1, j);
  if (curr != nullptr && curr->getCost() != -1) {
    neighbors.push_back(curr);
  }
  curr = (*this)(i, j - 1);
  if (curr != nullptr && curr->getCost() != -1) {
    neighbors.push_back(curr);
  }
  curr = (*this)(i, j + 1);
  if (curr != nullptr && curr->getCost() != -1) {
    neighbors.push_back(curr);
  }
  return neighbors;
}
uint32_t Graph::getHeight() { return m_height; }
uint32_t Graph::getWidth() { return m_width; }

GraphNode DFS::removeFromOpened() {
  auto temp = m_opened.top();
  m_opened.pop();
  return temp;
}

GraphNode BestFS::removeFromOpened() {
  auto temp = m_opened.top();
  m_opened.pop();
  return temp;
}

GraphNode BFS::removeFromOpened() {
  auto temp = m_opened.front();
  m_opened.pop();
  return temp;
}

bool BestFSComperator::operator()(const GraphNode &n1, const GraphNode &n2) {
  return n1.getCost() > n2.getCost();
}

bool AStar::AStarComperator::operator()(const GraphNode &n1,
                                        const GraphNode &n2) {
  return n1.getDist() > n2.getDist();
}

void AStar::removeFromPQ(std::priority_queue<GraphNode, std::vector<GraphNode>,
                                             AStar::AStarComperator> *pq,
                         GraphNode *node) {
  std::priority_queue<GraphNode, std::vector<GraphNode>, AStar::AStarComperator>
      cpy;
  while (!pq->empty()) {
    auto curr = pq->top();
    pq->pop();
    if (*node != curr) {
      cpy.push(curr);
    }
  }
  while (!cpy.empty()) {
    auto curr = cpy.top();
    cpy.pop();
    pq->push(curr);
  }
}
bool AStar::isNeighbors(GraphNode *node1, GraphNode *node2) {
  return (abs(node1->getRowIndex() - node2->getRowIndex()) == 0 &&
          abs(node1->getColIndex() - node2->getColIndex()) == 1) ||
         (abs(node1->getRowIndex() - node2->getRowIndex()) == 1 &&
          abs(node1->getColIndex() - node2->getColIndex()) == 0);
}
std::vector<GraphNode> AStar::search(Graph *graph, GraphNode *start,
                                     GraphNode *end) {
  if (start == nullptr || end == nullptr || start->getCost() == -1 ||
      end->getCost() == -1) {
    return std::vector<GraphNode>();
  }
  if (start == end || *start == *end) {
    return std::vector<GraphNode>();
  }
  auto &g = *graph;
  for (uint32_t i = 0; i < graph->getHeight(); ++i) {
    for (uint32_t j = 0; j < graph->getWidth(); ++j) {
      if (i == start->getRowIndex() && j == start->getColIndex()) {
        g(i, j)->setDist(0);
      } else {
        g(i, j)->setDist(std::numeric_limits<int>::max());
      }
      m_nodes.push(*(g(i, j)));
    }
  }
  while (!m_nodes.empty()) {
    auto current = m_nodes.top();
    m_nodes.pop();
    if (current == *end) {
      if (current.getSourceI() == start->getRowIndex() &&
          current.getSourceJ() == start->getColIndex() &&
          !isNeighbors(&current, start)) {
        return std::vector<GraphNode>();
      }
      std::vector<GraphNode> path;
      auto *node = &current;
      while (*node != *start) {
        path.emplace(path.begin(), *node);
        node = g(node->getSourceI(), node->getSourceJ());
      }
      path.emplace(path.begin(), *node);
      return path;
    }
    for (auto *neighbor : graph->getNeighbors(&current)) {
      if (isInDS(m_nodes, neighbor)) {
        auto alt = current.getDist() + neighbor->getCost();
        if (alt < neighbor->getDist()) {
          removeFromPQ(&m_nodes, neighbor);
          auto i = neighbor->getRowIndex(), j = neighbor->getColIndex();
          g(i, j)->setDist(alt);
          g(i, j)->setSource(current.getRowIndex(), current.getColIndex());
          m_nodes.push(*g(i, j));
        }
      }
    }
  }
  return std::vector<GraphNode>();
}

void deleteSpaces(std::string &str) {
  for (std::size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ' ' || str[i] == '\t') {
      str.erase(i);
    }
  }
}

std::vector<std::vector<int>> textToMat(const std::vector<std::string> &text) {
  std::vector<std::string> copy = text;
  for (auto it = copy.begin(); it != copy.end(); ++it) {
    deleteSpaces(*it);
  }

  uint32_t height = text.size(),
           width = std::count_if(text[0].begin(), text[0].end(),
                                 [](const char &c) { return c == ','; }) +
                   1;

  for (std::string line : text) {
    uint32_t numOfvals = std::count_if(line.begin(), line.end(),
                                       [](const char &c) { return c == ','; }) +
                         1;
    if (numOfvals != width) {
      throw exceptions::StatusException(exceptions::Status::wrongMatrix);
    }
  }

  std::vector<std::vector<int>> graph;
  for (uint32_t i = 0; i < height; ++i) {
    std::string line = text[i];
    std::vector<int> row;
    int start = 0, end = 0;
    for (uint32_t j = 0; j < width; ++j) {
      end = line.find_first_of(',', start);
      std::string val = line.substr(start, end - start);
      if (val == "b") {
        row.push_back(-1);
      } else {
        row.push_back(std::stoi(val));
      }
      start = end + 1;
    }
    graph.push_back(row);
  }
  return graph;
}

std::vector<std::vector<int>> parseMatrix(std::string &matrix) {
  std::vector<std::string> lines;
  std::string delimiter = ";";

  size_t pos = 0;
  std::string token;
  while ((pos = matrix.find(delimiter)) != std::string::npos) {
    token = matrix.substr(0, pos);
    lines.push_back(token);
    matrix.erase(0, pos + delimiter.length());
  }
  std::vector<std::string> vals(lines.begin() + 1, lines.end() - 2);
  matrix = (lines[lines.size() - 2] + ";" + lines[lines.size() - 1]);

  auto sizes = lines[0];
  auto sep = sizes.find_first_of(',');
  int height = std::stoi(sizes.substr(0, sizes.length() - sep - 1));
  int width = std::stoi(sizes.substr(sep + 1));
  auto actualMat = textToMat(vals);
  if (static_cast<int>(actualMat.size()) != height ||
      static_cast<int>(actualMat[0].size()) != width) {
    throw exceptions::StatusException(exceptions::Status::wrongMatrix);
  }
  return actualMat;
}

std::string parseNeighborsLocation(const GraphNode &src,
                                   const GraphNode &dest) {
  if ((src.getRowIndex() == dest.getRowIndex() - 1) &&
      (src.getColIndex() == dest.getColIndex())) {
    return "DOWN";
  }
  if (src.getRowIndex() == dest.getRowIndex()) {
    if (src.getColIndex() == dest.getColIndex() - 1) {
      return "RIGHT";
    } else if (src.getColIndex() == dest.getColIndex() + 1) {
      return "LEFT";
    }
  }
  if ((src.getRowIndex() == dest.getRowIndex() + 1) &&
      (src.getColIndex() == dest.getColIndex())) {
    return "UP";
  }
  return "";
}

std::string deleteSpacesFromMatrix(std::string str) {
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  str.erase(remove(str.begin(), str.end(), '\t'), str.end());
  str.erase(remove(str.begin(), str.end(), '\0'), str.end());
  return str;
}

std::string searchInGraph(std::string algorithm, std::string matrix,
                          std::mutex *mutex = nullptr) {
  cache::Cache cache;

  std::string toSearch = "\r\n";
  std::string replaceStr = ";";
  size_t pos = matrix.find(toSearch);
  while (pos != std::string::npos) {
    matrix.replace(pos, toSearch.size(), replaceStr);
    pos = matrix.find(toSearch, pos + replaceStr.size());
  }

  toSearch = ";;";
  replaceStr = ";";
  pos = matrix.find(toSearch);
  while (pos != std::string::npos) {
    matrix.replace(pos, toSearch.size(), replaceStr);
    pos = matrix.find(toSearch, pos + replaceStr.size());
  }

  matrix = deleteSpacesFromMatrix(matrix);

  if (mutex != nullptr) {
    mutex->lock();
  }
  auto solution = cache.searchSolutionFor(algorithm, matrix);
  if (mutex != nullptr) {
    mutex->unlock();
  }

  if (solution != "") {
    return solution;
  }

  auto matrixToSave = matrix;

  auto parsedMatrix = parseMatrix(matrix);

  int sep = matrix.find_first_of(';');
  std::string start = matrix.substr(0, matrix.length() - sep - 1);
  std::string end = matrix.substr(sep + 1);

  sep = start.find_first_of(',');
  int startX = std::stoi(start.substr(0, start.length() - sep - 1));
  int startY = std::stoi(start.substr(sep + 1));
  int endX = std::stoi(end.substr(0, end.length() - sep - 1));
  int endY = std::stoi(end.substr(sep + 1));

  Graph graph(parsedMatrix, parsedMatrix.size(), parsedMatrix[0].size());
  if (graph(startX, startY)->getCost() == -1 ||
      graph(endX, endY)->getCost() == -1) {
    throw exceptions::StatusException(exceptions::Status::noSolution);
  }
  if (start == end) {
    return "0," + algorithm;
  }
  std::vector<GraphNode> result;
  if (algorithm == "BFS") {
    BFS bfs;
    result = bfs.search(&graph, graph(startX, startY), graph(endX, endY));
  } else if (algorithm == "DFS") {
    DFS dfs;
    result = dfs.search(&graph, graph(startX, startY), graph(endX, endY));
  } else if (algorithm == "BestFS") {
    BestFS bestfs;
    result = bestfs.search(&graph, graph(startX, startY), graph(endX, endY));
  } else if (algorithm == "A*") {
    AStar astar;
    result = astar.search(&graph, graph(startX, startY), graph(endX, endY));
  } else {
    throw exceptions::StatusException(exceptions::Status::wrongInput);
  }

  if (result == std::vector<GraphNode>()) {
    throw exceptions::StatusException(exceptions::Status::noSolution);
  }

  int cost = 0;
  std::string message = algorithm;
  for (auto it = result.begin(); it != result.end(); ++it) {
    cost += it->getCost();
    if (it != result.begin()) {
      message += ",";
      message += parseNeighborsLocation(*(it - 1), *it);
    }
  }
  message = std::to_string(cost) + "," + message;

  if (mutex != nullptr) {
    mutex->lock();
  }
  cache.save(algorithm, matrixToSave, message);
  if (mutex != nullptr) {
    mutex->unlock();
  }

  return message;
}
} // namespace algorithms