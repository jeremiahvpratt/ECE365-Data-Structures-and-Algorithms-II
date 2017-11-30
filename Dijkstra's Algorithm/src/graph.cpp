//Graph class
//Jeremiah Pratt
//DSA 2 Assignment 3

#include "graph.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <string>


graph::graph(){
	numNodes = 0;						//keep track of inserted nodes
	knownNodes = new hashTable(1);		//hash table initialize to min size
}


void graph::addPath(const std::string &start, const std::string &dest, int l){
	
	adj tempAdj;
	graphNode tempNode;
	graphNode otherNode;
	if(!knownNodes->contains(start)){		//if node not in hash table,
		numNodes++;							//node doesn't exist, create new
		tempNode.id = start;
		//tempNode.numAdj = 1;
		tempAdj.adjId = dest;
		tempAdj.dist = l;
		tempNode.adjList.push_back(tempAdj);
		nodes.push_back(tempNode);
		knownNodes->insert(start,&nodes.back());	//add node to hash table
	}
	else{
		graphNode* n = static_cast<graphNode*>(knownNodes->getPointer(start));	//adding adj to known node
		tempAdj.adjId = dest;
		tempAdj.dist = l;
		n->adjList.push_back(tempAdj);
	}
	if(!knownNodes->contains(dest)){		//if adj is not in knownNodes, add it.
		numNodes++;
		otherNode.id = dest;
		nodes.push_back(otherNode);
		knownNodes->insert(dest,&nodes.back());
	}
}

bool graph::contains(const std::string &id){	//just a quick check fcn
	bool c = knownNodes->contains(id);
	return c;
}

void graph::dijkstra(const std::string &startNode){
	
	graphHeap = new heap(numNodes);
	int j = 0;
	for(std::list<graphNode>::iterator iterator = nodes.begin(); j < nodes.size(); ++iterator){
		if(iterator->id == startNode){					//setting start node to
			iterator->startDist = 0;					//distance 0
		}
		else{
			int max = (int)INT_MAX/2;					//all other nodes initialized to v large
			iterator->startDist = max;
		}
		iterator->visited = false;
		iterator->path = "";
		graphHeap->insert(iterator->id, iterator->startDist, &(*iterator));
		j++;
	}
	
	clock_t begin = clock();
	std::string id;
	std::string s;
	int i = graphHeap->deleteMin(&id);
	int useless;
	int c = 0;
	graphNode *n = static_cast<graphNode*>(knownNodes->getPointer(id));
	n->path = n->id;
	n->visited = true;
	while(i ==0){		//as long as deleteMin has a node to delete
		for(std::list<adj>::const_iterator iterator = n->adjList.begin(); iterator != n->adjList.end(); ++iterator){
			graphNode *adjg = static_cast<graphNode*>(knownNodes->getPointer(iterator->adjId));
			
			//The meat of Dijkstra:: if the current node's recorded minimum distance is longer
			//than a new available distance to the node, update that distance.
			if(adjg->startDist > iterator->dist + n->startDist && !(adjg->visited)){
				adjg->startDist = iterator->dist + n->startDist;
				adjg->path = n->path;			//my nifty little trick for getting
				adjg->path.append(", ");	    //the path strings
				adjg->path.append(adjg->id);
				
				//heap key records the current minimum distance to the node,
				//so that a deleteMin() operation removes the correct node.
				graphHeap->setKey(adjg->id,adjg->startDist); 
			}
		}
		//after all available nodes are checked/updated, remove the node with the smallest distance.
		i = graphHeap->deleteMin(&id, &useless, &n);
		n->visited = true;
	}
	clock_t end = clock();
	double eleapsed = ((double)(end-begin)) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time: " << eleapsed << std::endl;

}

void graph::outPaths(const std::string &fileName){
	
	std::ofstream file;
	file.open(fileName);
	
	for(std::list<graphNode>::const_iterator i = nodes.begin(); i != nodes.end(); ++i){
		if(i->startDist != (int)INT_MAX/2)
			file << i->id << ": " << i->startDist << " [" << i->path << "]\n";
		else
			file << i->id << ": NO PATH\n";
	}
	
	file.close();
}

