//Heap constructor
//Jeremiah Pratt
//DSA 2 Assignment 2

#include "hash.h"
#include <vector>
#include <string>

class heap{
	
	public:
		
		
		//Constructor that accepts the maximum size of the heap
		//as its only argument 
		heap(int size);
		
		// Inserts a node with the specified id string, key,
		// and optionally a pointer. They key is used to
		// determine the final position of the new node.
		// Returns:
		// 0 on success
		// 1 if the heap is already filled to capacity
		// 2 if a node with the given id already exists (but the heap
		// is not filled to capacity)
		int insert(const std::string &id, int key, void *pv = NULL); //DONE
		
		//Sets the key of the specified node to the specified value.
		//Returns 0 on success, 1 if a node with the given ID does not exist
		int setKey(const std::string &id, int key); //DONE
		
		//Returns the data associated with the smallest key, and deletes that node
		//from the binary heap.
		//if pId is supplied, write to that address the id of the node being deleted.
		//if pKey is supplied, write to that address the id of the key of the node being dleeted.
		//same with ppData, but associated pointer.
		//Returns 0 on success, 1 if a node with the given ID does not exist
		int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL); //DONE
		
		//Deletes the node with the specified id from the binary heap.
		//pKey and ppData are used as above, if supplied.
		//Returns 0 on success, 1 if a node with the given ID does not exist
		int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL); //DONE
		
	private:
	
		class node{
			
			public:
				
				std::string id;
				int key;
				void *pv;
		};
		
		int capacity;		//Maximum allowable size of the heap.
		int filled;			//Current number of full positions in the heap.
		//int numDel;
		
		std::vector<node> data;		//This vector acts as the heap structure
		
		hashTable *mapping;			//This hashTable allows for quick searching
									//within the heap
		
		//Finished all below
		void percolateUp(int posCur);		//For when you insert an element
		void percolateDown(int posCur);		//For when you remove an element
		int getPos(node *pn);				//Gets the position of a node 
		
};
	