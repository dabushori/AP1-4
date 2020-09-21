# Advanced Programming - Fourth Assignment
### Ori Dabush - 212945760
### Yorai Roth Hazan - 213251861
* * *
## Design:
### In this project we used:
* A server interface with 2 implementions:
  * SerialServer - only one user at a time.
  * ParallelServer - multiple users at a time. (with treads)
* The server deal with every user problem using a ClientHandler interface that has an implementions for each problem and every implemention has a Solver interface as a field that has a solve method that solve the problems.
* * *
## Files:
* server.h + server.cpp
* client_manager.h + client_manager.cpp
* client_handler.h + client_handler.cpp
* solver_manager.h + solver_manager.cpp
* * *
## Server class functions:
* open - open the server.
* talkWithClients - talk with the client/clients (abstract method)
* killServer - close the server
### SerialServer class functions:
* talkWithClients - talk with one client every time (override)
### ParallelServer class functions:
* threadFunction - deal with the threads
*  talkWithClients - talk with a couple of clients (override) (using ThreadPool)
## ClientHandler class function:
* handleClient - handle the client problem. (abstract)
## Client class function:
* Client - constructor
* inputToServer - send input to the server
* recvMessageFromServer - recieve from the server
* getFd - return the fd of the client
* killClient - close the client fd.
