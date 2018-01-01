//Main class
//Jeremiah Pratt
//DSA 2 Assignment 1

#include "hash.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	string dicName, checkName, outName, entry, line;
	clock_t t1, t2, t3, t4;
	hashTable *dictionary = new hashTable(50000);		//Initialize hash table to ~50,000 entries
	int ascii, test, lineCount, ins;
	bool ignore;
	
	
	cout << "Please enter the name of the dictionary file: ";
	cin >> dicName;
	
	
	t1 = clock();										//Timing length of dictionary load
	ifstream file(dicName.c_str());						//Initialize file read-in 
	
	if(file.is_open()){							//Read in file/write to
	
		while(file.good()){						//Hash table loop
			
			getline(file, entry);
			//entry.erase(entry.length()-1,1);			//Commented out newline erasure for you
			for(int i = 0; i < entry.length(); i++){
				entry[i] = tolower(entry[i]);			//All entries go lowercase
			}
			if(entry.length() > 0){
				ins = dictionary -> insert(entry);
			}
			//cout << ins << endl;
			if(ins == 2){
				cout << "rehashing failed! aborting program." << endl;
				return 0;
			}
		}
	}
	else{
		cout << "Error: dictionary file not found!\n";
		return 0;
	}
	file.close();
	t2 = clock();
	double diff = ((double)t2 - (double)t1) / CLOCKS_PER_SEC;
	cout << "Time required for dictionary load: " << diff << " seconds." << endl;
	
	
	cout << "Please enter the name of the document to be spell-checked: ";
	cin >> checkName;
	cout << "Please enter the name of the document to write the output to: ";
	cin >> outName;
	
	t3 = clock();
	ifstream ifs(checkName.c_str());				//Initializing file read-in
	ofstream outfile;								//Initializing results write-out
	outfile.open(outName.c_str());
	lineCount = 1;									//Variable needed to reference current line
	
	if(ifs.is_open()){
		
		entry = "";				//delete leftovers from dictionary read-in
		
		while(ifs.good()){
		
			getline(ifs, line);
			for(int i = 0; i < line.length(); i++){		//Loop thru line char by char
			
				ascii = line[i];						//We use ascii value to test
														//char validity
				while((ascii >= 48 && ascii <=57) || (ascii >= 65 && ascii <= 90) 
					|| (ascii >= 97 && ascii <= 122) || ascii == 45 || ascii == 39){
					   
					entry.push_back(line[i]);			//append each char until invalid char appears
					i++;
					
					if(ascii >= 48 && ascii <= 57){		//Ignore words with numbers in them
						ignore = true;
					}
					
					ascii = line[i];
					   
				}
				
				if(entry == ""){						//Fix for blank line lookups
					ignore = true;
				}
				
				if(!ignore){
					
					for(int i = 0; i < entry.length(); i++){	//Checks against all lowercase
						entry[i] = tolower(entry[i]);
					}
					if(entry.length() > 20){
						outfile << "Long word at line " << lineCount << ", starts: "
						<< entry.substr(0,20) << "\n";
					}
					else if(!(dictionary -> contains(entry))){
					
						outfile << "Unknown word at line " << lineCount << ": " << entry << "\n";
					}
					//cout << "checking word: " << entry << endl;
				
				}
				
				ignore = false;
				entry = "";
			}
		
			lineCount ++;
		}
	}
	else{
		cout << "Error: spell check file not found!\n";
		return 0;
	}
	t4 = clock();
	diff = ((double)t4 - (double)t3) / CLOCKS_PER_SEC;
	cout << "Time required for spell check: " << diff << " seconds." << endl;
	ifs.close();
	return 0;
}
