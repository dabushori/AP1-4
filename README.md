# Advanced Programming - Fourth Assignment
### Ori Dabush - 212945760
### Yorai Roth Hazan - 213251861
* * *
## Design:
### In this project we used:
* A server interface with 2 implementions:
  * SerialServer - only one user at a time.
  * ParallelServer - multiple users at a time. (with treads)
* The server deal with each user problem using a ClientHandler interface that has an implementions for each server and our implemention (GraphClientHandler) uses a function that uses algorithms.cpp functions to solve the problem in handleClient.
* If the problem was already solved before it will be in the cache and the server will use the cache to get the solution and it will not solve the problem again.
* * *
## Exceptions:
* Status: 0 - success
* Status: 1 - noSolution
* Status: 2 - wrongMatrix
* Status: 3 - wrongInput
* Status: 4 - noCacheDir
* Status: 5 - cacheFileError
* Status: 6 - timeoutPassed
* If any server function did not work (socket, bind, accept .... ) we will return errno error (system_category).
* * *
## Files:
* server.h + server.cpp
* client_manager.h + client_manager.cpp
* client_handler.h + client_handler.cpp
* exceptions.cpp + exceptions.h
* paths.cpp + paths.h
* cache.cpp + cache.h
* algorithms.cpp + algorithms.hpp
* * *
# Those are the classes that we created in the files above:
## Server class functions:
* rule of 5 and constructor - They forced a destructor on abstract so i added all of them as a default.
* open - open the server.
* talkWithClients - talk with the client/clients. (abstract method)
* killServer - close the server.
### SerialServer class functions:
* default constructor.
* talkWithClients - talk with one client every time. (override)
### ParallelServer class functions:
* threadFunction - deal with the threads. (friend function)
*  talkWithClients - talk with a couple of clients. (override) (using ThreadPool)
* * *
## ClientHandler class function:
* constructor.
* rule of 5 - They forced a destructor on abstract so i added all of them as a default.
* recvMessageFromClient - recieve a message from the client. (abstract)
* handleClient - handle the client problem. (abstract)
### GraphClientHandler class function:
* constructor.
* recvMessageFromClient - recieve a message from the client. (override)
* handleClient - handle the client problem which is to find a path in a matrix to the end. (override)
* formatAnswer - change the answer of the problem to the answer in the format of the assignment.
* * *
## Client class functions:
* constructor.
* getFd - return the fd of the client.
* killClient - close the fd of the client.
* * *
## Chace class functions:
* constructor
* save - save a solution in the cache
* searchSolutionFor - search for the solution in the cache.
* clear - delete all the solutions from the cache.
### namespace paths function:
* hasEnding - checks if a string ends with another string.
* findPathToCacheDirectory - return the path of the cache.
* * *
## StatusException class functions:
* two constructors.
* getStatus - get what is the exception.
* * *
## GraphNode class functions:
* two constructors.
* getters to all the members. (i, j, iSrc, jSrc, cost, dist)
* setters to all the members. (i, j, iSrc, jSrc, cost, dist)
* operator== - checks if two nodes are equal.
* operator!= - checks if two nodes are not equal.
## Graph class functions:
* constructor. (2D array of GraphNode[2 vectors], height, width)
* *operator(i, j) - get the value in the index i and j.
* getNeighbors - returns the neighbors of the node.
## template <typename DS> class Searcher functions:
* rule of 5 and constructor - They forced a destructor on abstract so i added all of them as a default.
* addToOpened - add a node to the opened list.
* removeFromOpened - remove a node from the opened list (abstract)
* isDSEmpt - checks if the opened list is empty.
* isInClosed - checks if the node is in the closed list.
* search - search a path in the graph using different algorithms. (virtual)
### BestFSComperator class fucntions:
* operator(n1, n2) - compare 2 different nodes for the priority queue.
### class BFS : public Searcher<std::queue<GraphNode>> functions:
* removeFromOpened - remove a node from the opened list. (override)
### class DFS : public Searcher<std::stack<GraphNode>> functions:
* removeFromOpened - remove a node from the opened list. (override)
### class BestFS : public Searcher<std::priority_queue<GraphNode, std::vector<GraphNode>, BestFSComperator>> functions:
* removeFromOpened - remove a node from the opened list. (override)
### isElementInPQ- a method to check if an element is in the priority queue.
## AStar class:
### class AStarComperator (inside Astar class) functions:
* operator(n1, n2) - compare 2 different nodes for the priority queue.
### Functions of Astar class:
* isInDS - a method to check if an element is in the data structure. (template)
* removeFromPQ - remove an element from the priority queue.
* isNeighbors - check if 2 nodes are neighbors.
* search - search a path in a graph using A* algorithm.
### namespace algorithms functions (methods we used out of classes):
* deleteSpaces - a method to delete spaces and tabs from a string.
* textToMat - parse a vector of strings into matrix
* parseMatrix - a method to parse a string into a matrix. the string is build in the assignment format.
* parseNeighborsLocation - parse 2 nodes (source and destination) into an action (UP, DOWN, LEFT or RIGHT)
* searchInGraph - search path in a graph using a given algorithm and a cache.
* * *
## Tests:
* We tested each algorithm with our own custom made tests.
* we tested the server functions with a main tester (we used python to run it on the computer).
* we tested the server and the algorithms while running the project on our computers.
* we tested the parallel server with a python file that we created that run 10 threads.

