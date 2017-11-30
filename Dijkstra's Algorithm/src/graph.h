//Header file for graph class
//Jeremiah pratt
//DSA 2 Assignment 3


#include "heap.h"
#include <string>
#include <vector>
#include <list>
#include <climits>

class graph {
	
	public:
	
		graph();
		
		//Inserts a new edge, and possibly a new node, into the graph.
		//Returns 0 upon success
		void addPath(const std::string &start, const std::string &dest, int l);
		
		//Returns true if the graph contains the node with the specified ID,
		//Returns false otherwise.
		bool contains(const std::string &id);
		
		//Applies dijkstra's algorithm from a provided starting node,
		//Return type is void because all work is done internally,
		//No output given from here.
		void dijkstra(const std::string &startNode);
		
		//Given a file name, outputs the shortest paths
		//To the nodes in the same order the nodes were input
		void outPaths(const std::string &fileName);
	
	private:
	
	
		//Adjacency list class
		class adj{
					
			public:
						
				std::string adjId;    //key of adjacent node
				int dist;		  //distance to adjacent node
					
		};
		
		class graphNode{
			
			public:
			
				std::string path;			//path taken from start node
				std::string id;				//ID string of node
				std::list<adj> adjList;		//list of adjacent nodes
				bool visited;
				int numAdj;
				int startDist;				//distance to start node 
											//initialize to zero											
				
		};
		
		int numNodes;				//number of nodes in graph 
		//std::list<graphNode*>::const_iterator iter;
		std::list<graphNode> nodes;	//list of all known nodes in graph
		
		int max = INT_MAX;
		heap *graphHeap;
		hashTable *knownNodes;     //for fast searching of nodes
		
		
};
