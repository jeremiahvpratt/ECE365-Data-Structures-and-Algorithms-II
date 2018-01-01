//Checks if 2 strings have been "merged" in a valid fashion
//Jeremiah Pratt
//DSA 2 Assignment 4

#include <string>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;


bool valid[1002][1002] = {{true}};		//memoization step
string mergedBoi;						//stores the merged string with capitalized characters from A

//Recursively checks if two strings are a valid merge.
//At each step, returns true if validity is computed.
//If false is returned and indices are valid, false is stored in lookup table
//for efficient computing further down the line
//Returns true if c is a valid merge of a and b, returns false otherwise
bool checkMerge(string &a, string &b, string &c, int aInd, int bInd){
	
	int cInd = aInd + bInd;		//Indexing along merged string
	bool temp1,temp2;			//Store output from checkMerge
	string tempStr;				//Working variable for final output string
	char tempChar;				//capitalization tool
	
	if(!valid[aInd][bInd])		//Check if false already stored in lookup table
		return false;
	
	if((aInd == a.length() && bInd == b.length()))	//terminating condition that means valid merge, assuming len(c) = len(a) + len(b)
		return true;
	
	if(a[aInd] == c[cInd]){							//recursive check moving forward one index in a
		temp1 = checkMerge(a,b,c,aInd+1,bInd);
		if(temp1){									//updates the merged string beforere returning true
			tempChar = a[aInd];
			tempChar = (toupper(tempChar));
			string tempyStr(1,tempChar);
			tempyStr.append(mergedBoi);
			mergedBoi = tempyStr;
			return true;
		}
	}
	
	if(b[bInd] == c[cInd]){							//recursive check moving forward one index in b
		temp2 = checkMerge(a,b,c,aInd,bInd+1);
		if(temp2){									//updates the merged string before returning true
			tempStr = b[bInd];
			tempStr.append(mergedBoi);
			mergedBoi = tempStr;
			return true;
		}
	}
	
	valid[aInd][bInd] = false;						//if neither condition is met, this index is memoized as false, and false is returned 
	return false;
}
	
	
int main(){
	
	string a, b, c; //Strings to be checked
	string fname,fout;	//Name of file to be read from
	bool check;		//value that determines validity of merge
	
	cout << "Please enter the name of the file to be checked: ";
	cin >> fname;
	
	cout << "Please enter the name of the file to be written to: ";
	cin >> fout;
	
	ifstream inFile;		//read in
	inFile.open(fname);
	
	ofstream outFile;
	outFile.open(fout);		//read out
	
	if(!inFile){							//Error check
		cerr << "Unable to open file.";
		exit(1);
	}
	
	while(inFile >> a){		//read in a,b,c
		
		inFile >> b;
		inFile >> c;
		memset(valid, true, sizeof(valid));		//most efficient reset of boolean array
		mergedBoi = "";		//merged string reset
		
		if((a.length() + b.length()) != c.length())		//check to make sure strings are valid sizes
			check = false;
		else
			check = checkMerge(a,b,c,0,0);		//check function call
		
		if(check)
			outFile << mergedBoi << "\n";
		else{
			outFile << "*** NOT A MERGE ***\n";
		}
	}
	inFile.close();
	outFile.close();
	
	return 0;
}
	