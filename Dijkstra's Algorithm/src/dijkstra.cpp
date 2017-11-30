//Main file

#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

//read-in file function, not sure if style used is considered "sloppy"
//but we have a garunteed file format, so no problems here.
void doTheReadThing(const string &file, graph* g){
	ifstream inFile;
	inFile.open(file);
	if(!inFile){
		cerr << "Unable to open file.";
		exit(1);
	}
	string s,start,end;
	int dist;
	int i = 0;
	while(inFile >> s){
		start = s;
		inFile >> s;
		end = s;
		inFile >> s;
		dist = stoi(s);
		g->addPath(start,end,dist);
		i++;
	}
	inFile.close();
	return;
}

int main(){
	graph *g = new graph();
	string fname;
	string id = "";
	
	cout << "Please enter the filename of your graph: ";
	
	cin >> fname;
	
	doTheReadThing(fname,g);
	
	cout << "Please enter the name of the starting node: ";
	cin >> id;
	while(!g->contains(id)){
		cout << "Please enter a valid name: ";
		cin >> id;
	}
	
	
	g->dijkstra(id);
	
	cout << "Please enter the name of the file to write to: ";
	cin >> fname;
	g->outPaths(fname);
	return 0;
}