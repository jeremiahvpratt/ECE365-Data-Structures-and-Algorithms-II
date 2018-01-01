# Hash
Design and implementation of simple hash table in C++
Version 1.0.0 Uploaded 9/26/17

hash.cpp is a simple hash table class, which stores "hashItem" data points in a resizeable vector. The hash function relies on bitwise XOR operations for swift and highly randomized return values, resulting in minimal clustering while ensuring low processing times. 

dictionary.cpp implements hash.cpp to read in and store a dictionary of words stored in a text file, and then check that dictionary against a document to return misspelled or not-found words.