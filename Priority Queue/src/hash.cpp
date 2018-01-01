//Hash table class
//Jeremiah Pratt
//DSA 2 Assignment 1

#include "hash.h"
#include <iostream>

int primes[20] = {98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
				  12582917, 25165843, 50331653, 100663319, 201326611};


//Constructor for initializing hash table, takes pointer to initiated size
//And sets size equal to a prime number larger than the specified size
hashTable::hashTable(int size){
	capacity = getPrime(size);
	data.resize(capacity);
	filled = 0;
	for(int i = 0; i < capacity; i++){
		data[i].isOccupied = false;
		data[i].isDeleted = false;
	}
}

//Function for assigning hash address in vector
//Utilizes bitwise XOR with large primes
//Source: https://stackoverflow.com/questions/8317508/hash-function-for-a-string
int hashTable::hash(const std::string &key){
	unsigned h = 37;
	for(std::size_t i = 0; i < key.length(); i++){
		h = (h * 54059) ^ (key[i] * 76963);
	}
	return h % capacity;
}


//Function for finding the position of a key in the hash table
int hashTable::findPos(const std::string &key){
	
	unsigned h = hash(key);		//address in hash table
	
	while(data[h].isOccupied){	
	
		if(data[h].key == key){
			
			if(data[h].isDeleted){
				return -1;			
			}
	
			else{
				return h;
			}
			
		}
		
		else{
			h++;
			
			if(h == capacity){
				h = 0;
			}
		}
		
	}
	
	return -1;
}

//Returns true if the key is in hash table,
//False otherwise
bool hashTable::contains(const std::string &key){
	int pos = findPos(key);
	if(pos == -1){
		return false;
	}
	else{
		return true;
	}
}

//Inserts new value into the hash table
int hashTable::insert(const std::string &key, void *pv){
	std::cout << "filled: " << filled << " capacity: " << capacity << std::endl;
	if((2*filled) >= capacity){
		bool didItFail = rehash();
		if(!didItFail){
			return 2;
		}
	}
	//std::cout << "break 1" << std::endl;
	unsigned h = hash(key);
	int delSpot = -1;
	
	int catchH = h - 1;
	
	/**
	if(data[h].isOccupied){
		std::cout << "key for " << key << " occupied!\n";
	}
	*/
	while(data[h].isOccupied){
		if(data[h].key == key){
			
			if(!(data[h].isDeleted)){
				return 1;
			}
			
			else{
				data[h].isDeleted = false;
				return 0;
			}
		}
		
		else if(data[h].isDeleted && delSpot == -1){
			delSpot = h;
		}
		h ++;
		if(h == capacity)
			h = 0;
	}
	if(delSpot != -1){
		h = delSpot;
	}

	//std::cout << h << "\n";
	
	data[h].key = key;
	data[h].isOccupied = true;
	data[h].isDeleted = false;
	data[h].pv = pv;
	
	filled++;
	return 0;
}

//Function for finding the next largest "good" hash prime for table size 
unsigned int hashTable::getPrime(int size){
	int addr = 0;
	int i = 0;
	while(addr == 0){
		if(size < primes[i]){
			addr = i + 1;		//adding 1 to avoid missing the mark when size < primes[0]
		}
		i ++;
	}
	return primes[addr - 1];    //don't forget to remove your +1 fix!!!
}

//When hash table becomes 50% filled, rehash with capacity doubled.
bool hashTable::rehash(){
	
	//std::cout << "rehashing\n";
	std::vector<hashItem> temp = data;		//Move everything to temp vector
	int oldCap = capacity;					//old capacity value
	capacity = getPrime(capacity * 2);		//Set capacity to ~double
	
	try{
		data.resize(capacity);
	}
	catch(std::bad_alloc){
		std::cout << "BAD MEMORY ALLOCATION\n";
		return false;
	}
	
	
	for(int i = 0; i < capacity; i++){		//Empty table
		data[i].isOccupied = false;
		data[i].isDeleted = false;
	}
	
	
	for(int i = 0; i < oldCap; i++){		//Now we insert it all back!!
		if(temp[i].isOccupied = true){
			insert(temp[i].key);
		}
	}
	//std::cout << "rehash complete\n";
	return true;
}

void* hashTable::getPointer(const std::string &key, bool *b){
	int pos = findPos(key);
	
	if(b != NULL){
		if(pos == -1){
			*b = false;
			return NULL;
		}
		else{
			*b = true;
			return data[pos].pv;
		}
	}
	else{
		if(pos == -1)
			return NULL;
		else
			return data[pos].pv;
	}
}

int hashTable::setPointer(const std::string &key, void *pv){
	
	int pos = findPos(key);
	
	if(pos == -1)
		return 1;
	
	else{
		data[pos].pv = pv;
		return 0;
	}
}

bool hashTable::remove(const std::string &key){
	int pos = findPos(key);
	
	if(pos == -1)
		return false;
	
	else{
		data[pos].isDeleted = true;
		return true;
	}
}