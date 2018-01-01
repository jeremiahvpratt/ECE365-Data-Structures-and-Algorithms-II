# Dijkstra's Algorithm

Design and implementation of Dijkstra's Algorithm for an undirected graph, utilizing previously built hash and heap classes. 
Version 1.0.0 uploaded 11/18/17

graph.cpp is a rudimentary graph class, which stores a vector of nodes, each of which contains its own vector of adjacent nodes and the weights between those two nodes. Pointers to the primary nodes are also stored in a hash library for constant time searching. The class contains a method for adding nodes as well as a method for determining if a given node currently exists in the vector. Finally the class also contains the main Dijkstra's Algorithm method.

dijkstra.cpp is the main class used for executing the above algorithm. It reads in a list of nodes from a file specified by the user and stores them in the above graph class, before calling the Dijkstra method and writing the results to another file, also specified by the user.
