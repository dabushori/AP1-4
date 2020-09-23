# Advanced Programming - Fourth Assignment
### Ori Dabush - 212945760
### Yorai Roth Hazan - 213251861
* * *
## Design:
### In this project we used:
* A server interface with 2 implementions:
  * SerialServer - only one user at a time.
  * ParallelServer - multiple users at a time. (with treads)
* The server deal with every user problem using a ClientHandler interface that has an implementions for each server and our implemention uses function that uses algorithms.cpp functions to solve the problem in handleClient.
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
## Server class functions:
* open - open the server.
* talkWithClients - talk with the client/clients. (abstract method)
* killServer - close the server.
### SerialServer class functions:
* talkWithClients - talk with one client every time. (override)
### ParallelServer class functions:
* threadFunction - deal with the threads.
*  talkWithClients - talk with a couple of clients. (override) (using ThreadPool)
## ClientHandler class function:
* constructor.
* recvMessageFromClient - recieve a message from the client. (abstract)
* handleClient - handle the client problem. (abstract)
### TestClientHandler class function:
* constructor.
* recvMessageFromClient - recieve a message from the client. (override)
* handleClient - handle the client problem which is to find a path in a matrix to the end. (override)
* formatAnswer - change the answer of the problem to the answer in the format of the assignment.
## Client class functions:
* constructor
* inputToServer - send a message to the server.
* recvMessageFromServer - recieves a message from the server.
* getFd - return the fd of the client.
* killClient - close the fd of the client.
## Chace class functions:
* constructor
* save - save a solution in the cache
* searchSolutionFor - search for the solution in the cache.
* clear - delete all the solutions from the cache.
## StatusException class functions:
* two constructors.
* getStatus - get what is the exception.
### namespace paths function:
* hasEnding - checks if a string ends with another string.
* findPathToCacheDirectory - return the path of the cache.

* * *
## Tests:
* We tested each algorithm with our own custom made tests.
* we tested the server functions with a main tester.
* we tested the server and the algorithms while running the project on our computers.

