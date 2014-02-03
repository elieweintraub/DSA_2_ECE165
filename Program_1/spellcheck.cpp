/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #1                                              */
/*                                                                              */ 
/*  spellcheck.cpp                                                              */
/*                                                                              */
/*  This sourcefile uses the hashTable class defined in hash.h and implemented  */
/*  in hash.cpp as part of a simple spellcheck program, that takes a dictionary */
/*  file, reads it into a hashTable, and then checks an inputfile file,         */
/*  outputting all unknown words and long words to an output file.              */
/*                                                                              */
/********************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
#include "hash.h"

using namespace std;

//load_dictionary prompts the user for a dictionary file and reads the given dictionary file
//into a hashtable that is passed in as a parameter, converting all letters to lower case
// as the dictionary is being read in.
void load_dictionary( hashTable &); 
//the heart of the program spell_check, prompts the user for an input file(the document to be
//spell checked) and for an output file, and then spell checks the input file, writing to the
//output file all unrecognized words and all words longer than 20 characters. All letters are 
//converted to lower case, as the spell check is case insensitive.  
void spell_check(hashTable &);
//convertToLower is a helper function used in load_dictionary. It takes a string reference and
//converts all uppercase characters to lowercase, returning a reference to the string passed in.
string & convertToLower(string &);
//The main function, it calls routines to read in the dictionary and spell check the document.
//The time to load the dictionary as well as the time to spell check are calculated using CPU
//time and printed to standard output.
main(){ 
	hashTable  dictionaryTable(50000);
	clock_t t1,t2;
	double timeDiff;
	
	//Load dictionary and output the time it takes
	t1 = clock();
	load_dictionary(dictionaryTable);
	t2 = clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << timeDiff<< endl;

	//Spell check the document and output the time it takes
	t1=clock();
	spell_check(dictionaryTable);
	t2=clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to check document: " << timeDiff<< endl;

	return 0;
}

//The load_dictionary routine
void load_dictionary(hashTable &dictionaryTable){
	string dictionaryName,word;
	
	cout<<"Enter name of dictionary: ";
	cin>>dictionaryName;
	
	ifstream dictionary(dictionaryName.c_str());
	if (!dictionary.is_open()){ // Error opening input file
		cerr << "Unable to open dictionary file: "<<dictionaryName<<endl;
		exit(1);
	}

	while(dictionary>>word)
		//insert words into the hashTable checking that there are no memory allocation failures
		if((dictionaryTable.insert(convertToLower(word)))==2){ 
			cerr<<"Could not resize hashTable! Memory allocation failure!"<<endl;
			exit(1);
		}

	dictionary.close();
 }
 
 //The spell_check routine
 void spell_check(hashTable &dictionaryTable){
	string inputFileName, outputFileName;
	
	cout<<"Enter name of input file: ";
	cin>>inputFileName;
	
	ifstream input(inputFileName.c_str());
	if (!input.is_open()){ // Error opening input file
		cerr << "Unable to open input file: "<<inputFileName<<endl;
		exit(1);
	}
	
	cout<<"Enter name of output file: ";
	cin>>outputFileName;
	
	ofstream output(outputFileName.c_str());
	if (!output.is_open()){ // Error opening output file
		cerr<< "Unable to open output file: "<<outputFileName<<endl;	
		exit(1);
	}
	
	string word("");
	char letter;
	bool hasDigit(false);
	int numOfChars(0),lineNum(1);
	
	while (input.good()){
		input.get(letter);
		//If char is digit, set hasDigit flag which tells us not to further grow  
		//the word and not to check in dictionary
		if (isdigit(letter)){ 
			hasDigit=true;
			numOfChars++; //done primarily to ensure numOfChars>0 (not to keep accurate count)
		}
		//Else if char is any other valid charicter check hasDigit flag. If true do nothing. If 
		//false, check letter counter.If less than 20 grow word. Update letter counter.
		else if(isalpha(letter) || letter=='\'' || letter=='-'){ 
			if(hasDigit==false){
				if(numOfChars<20){ //grow the word
					word+=tolower(letter);
				}						
				numOfChars++; 
			}		
		}
		//Else char is non-valid.We reached a word delimiter. Do all requisite processing
		//on the word and refresh the word holder, hasDigit flag, and letter counter.
		//Also, check for newline char in order to update line number. 
		else{ 
			if(numOfChars>0){ //only do processing if there is a word to process
				if(hasDigit==false ){
					if(numOfChars>20)
						output<<"Long word at line "<<lineNum<<", starts: "<<word<<endl;
					else if(dictionaryTable.contains(word)==false)
						output<<"Unknown word at line "<<lineNum<<": "<<word<<endl;
				}
				//refresh word holder, hasDigit flag and letter counter
				word="";
				numOfChars=0;
				hasDigit=false;
			}
			if(letter=='\n')
				lineNum++;
		}
	}
	//Do a final check after having reached end of file,since last line doesn't end with '\n' 
	if(numOfChars>=1){ //only do processing if there is a word to process
		if(hasDigit==false ){
			if(numOfChars>20)
				output<<"Long word at line "<<lineNum<<", starts: "<<word<<endl;
			else if(dictionaryTable.contains(word)==false)
				output<<"Unknown word at line "<<lineNum<<": "<<word<<endl;
		}
	}
	
	input.close();
	output.close();	
}

//The convertToLower helper function
string& convertToLower(string &word){
	for (int i=0; i<word.length(); i++){
		word[i]=tolower(word[i]);
	}
	return word;
}
