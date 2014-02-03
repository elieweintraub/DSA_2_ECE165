/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #4                                              */
/*                                                                              */ 
/*  merge.cpp                                                                   */
/*                                                                              */
/*  This sourcefile prompts the user for an input file consisting of sets of    */
/*  three strings and checks if each third string in a set is a "merge" of the  */
/*  previous two strings in the set. Results are outputted to an output file.   */
/*                                                                              */
/********************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//Global Variables
const int MAX_WORD_LENGTH=1000;               // Maximum length of str_A and str_B
bool M[MAX_WORD_LENGTH+1][MAX_WORD_LENGTH+1]; // Matrix for dynamic programming routine 
string str_A="",str_B="",str_C="";            // str_C is potential merge of str_A & str_B

//isMerge: Dynamic programming routine which checks for valid merges
//Uses the global variables str_A,str_B,str_C, and M.
//Checks for valid i-j merges, where an i-j merge is a valid merge consiting of
//the first i letters of string B and the first j letters of string A
//Returns true if str_C is a valid merge of str_A and str_B; returns false otherwise 
bool isMerge(){
	if( str_A.size()+str_B.size()!=str_C.size())
		return false; //sizes don't match.NO VALID MERGE
	else{ // sizes match. Use dynamic programming routine to fill matrix M.		 
		int n=str_A.size();  // # of significant columns -1 (index of last  significant column)
		int m=str_B.size();  // # of significant rows -1 (index of last significant row)
		int i,j;      // for indexing rows and columns 
		bool new_A;   // condition for valid i-j merge if the present letter of C is from string A
		bool new_B;   // condition for valid i-j merge if the present letter of C is from string B
		
		//Initialize first row and column of matrix M
		for (j=0; j<n; j++){
			if(str_A[j]==str_C[j])
				M[0][j+1]=true;
			else{ // set remaining values to false
				for (;j<n; j++)
					M[0][j+1]=false;
				break;
			}	
		}		
		for (i=0;i<m;i++){
			if (str_B[i]==str_C[i])
				M[i+1][0]=true;
			else{ // set remaining values to false
				for (;i<m;i++)
					M[i+1][0]=false;
				break;
			}
		}
		//Fill rest of matrix
		for(i=1;i<=m;i++){
			for(j=1;j<=n;j++){
				new_A=((str_C[i+j-1]==str_A[j-1])&& (M[i][j-1])); 
				new_B=((str_C[i+j-1]==str_B[i-1])&& (M[i-1][j]));
				M[i][j]=(new_A||new_B);
			}
		}
		return M[m][n]; 
	}
}		

//printMerge: Takes as a parameter a boolean indicating whether or not there was a valid merge.
//If there was a valid merge prints out the merge by capitalizing  the characters from str_A.
//Uses the global variables str_A,str_B,str_C, and M. 
string &printMerge(bool validMerge){
	if(!validMerge)
		str_C="*** NOT A MERGE ***";
	else{
		int j=str_A.size();
		int i=str_B.size();
		while(i>0 && j>0){
			if(M[i-1][j]) // a character from str_B was added to the merge
				i--;
			else{ // a character from str_A was added to the merge
				j--; // Doing this first makes i+j the correct index into str_C
				str_C[i+j]=toupper(str_C[i+j]); // Convert character to uppercase
			}
		}
		if (i==0)
			while(j>0){
				j--; // Doing this first makes j the correct index into str_C
				str_C[j]=toupper(str_C[j]); // Convert character to uppercase
			}
	}
	return str_C;
}

//The main routine
int main(){
	string inputFileName, outputFileName;
	
	//Prompt user for input file name and verify that opens properly
	cout<<"Enter name of input file: ";
	cin>>inputFileName;
	
	ifstream input(inputFileName.c_str());
	if (!input.is_open()){ // Error opening input file
		cerr << "Unable to open input file: "<<inputFileName<<endl;
		exit(1);	
	}
	
	//Prompt user for output file name and verify that opens properly
	cout<<"Enter name of output file: ";
	cin>>outputFileName;
	
	ofstream output(outputFileName.c_str());
	if (!output.is_open()){ // Error opening input file
		cerr << "Unable to open output file: "<<outputFileName<<endl;
		exit(1);	
	}
	
	//Process input file
	while(input.good()){
		str_A=str_B=str_C=""; //refresh strings
		input>>str_A>>str_B>>str_C;
		if(str_A!="") //a set of strings were read in		
			output<<printMerge(isMerge())<<endl; //check for merge and output result		
	}
	return 0;	
}	
	