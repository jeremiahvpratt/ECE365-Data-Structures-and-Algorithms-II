//Heap class
//Jeremiah Pratt
//DSA 2 Assignment 2

#include "heap.h"
#include <iostream>

heap::heap(int size){
	capacity = size;
	data.resize(capacity+1);
	mapping = new hashTable(capacity*2);
	filled = 0;
	//numDel = 0;
}
	
int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

void heap::percolateUp(int posCur){
	
	node temp = data[posCur];			
	

	//Loops as long as the element is smaller than the one above it in
	//the heap.
	for(; (posCur > 1 && temp.key < data[posCur/2].key); posCur = posCur/2){
		data[posCur] = data[posCur/2];
		mapping -> setPointer(data[posCur].id, &data[posCur]);
	}
	
	//Finally, bring in the element that was swapped multiple times 
	data[posCur] = temp;
	mapping -> setPointer(data[posCur].id, &data[posCur]);
}


void heap::percolateDown(int posCur){
	
	node temp = data[posCur];			//swapped multiple times
	
	int t, left, right;
	
	while(posCur * 2 <= filled){
		left = posCur * 2;
		right = left + 1;
		if(left < filled && data[right].key < data[left].key)
			t = right;
		else
			t = left;
		
		if(data[t].key < data[posCur].key){
			data[posCur] = data[t];
			mapping -> setPointer(data[posCur].id, &data[posCur]);
		}
		else
			break;
		
		posCur = t;
	}
	
	data[posCur] = temp;
	mapping -> setPointer(data[posCur].id, &data[posCur]);
}	

int heap::insert(const std::string &id, int key, void *pv){
	//std::cout << "filled: " << filled << " capacity: " << capacity << "\n";
	//std::cout << "break -1" << std::endl;
	if(filled < capacity){
		//std::cout << "break 0" << std::endl;
		if(!(mapping->contains(id))){
			//std::cout << "break 1" << std::endl;
			filled ++;
			//std::cout << "break 2" << std::endl;
			data[filled].id = id;
			//std::cout << "break 3" << std::endl;
			data[filled].key = key;
			//std::cout << "break 4" << std::endl;
			data[filled].pv = pv;
			//std::cout << "break 4" << std::endl;
			
			mapping->insert(id, &data[filled]);
			//std::cout << "break 5" << std::endl;
			percolateUp(filled);
			//std::cout << "break 6" << std::endl;
			
			return 0;
		}
		else
			return 2;
	}
	else
		return 1;
}


int heap::setKey(const std::string &id, int key){
	
	if(mapping->contains(id)){
		node *pn = static_cast<node *> (mapping->getPointer(id));
		
		int old = pn->key;
		pn->key = key;
		int pos = getPos(pn);
		
		if(old < key)
			percolateDown(pos);
		if(key < old)
			percolateUp(pos);
		
		return 0;
	}
	else
		return 1;
}
	
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	
	if(filled != 0){
		if(pId != nullptr)
			*pId = data[1].id;
		if(pKey != nullptr)
			*pKey = data[1].key;
		if(ppData != nullptr)
			*(static_cast<void**> (ppData)) = data[1].pv;
		mapping->remove(data[1].id);
		if(filled > 1)
			data[1] = data[filled];
		filled--;
		//numDel++;
		//std::cout << "deleted: " << numDel << "\n";
		if(filled > 1)
			percolateDown(1);
		
		return 0;
	}
	else
		return 1;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
	
	if(mapping->contains(id)){
		
		node *pn = static_cast<node *> (mapping->getPointer(id));
		
		int old = pn->key;
		int pos = getPos(pn);
		
		if(pKey != nullptr)
			*pKey = data[pos].key;
		if(ppData != nullptr)
			*(static_cast<void**> (ppData)) = data[pos].pv;
		
		mapping->remove(data[pos].id);
		data[pos] = data[filled];
		filled--;
		//numDel++;
		//std::cout << "deleted: " << numDel << "\n";
		if(data[pos].key < old)
			percolateDown(pos);
		else if(data[pos].key > old)
			percolateUp(pos);
		
		return 0;
	}
	else
		return 1;
}