/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #1                                              */
/*                                                                              */ 
/*  hash.cpp                                                                    */
/*                                                                              */
/*  This sourcefile implements all of data members and member functions of      */
/*  the hashTable class defined in hash.h .                                     */
/*                                                                              */
/********************************************************************************/



#include <iostream>
#include <cstdlib>

#include "hash.h"

using namespace std;

hashTable::hashTable(int size):
	filled(0),capacity(getPrime(size)),data(capacity){}

int hashTable::insert(const string &key, void *pv){
	int currentPos=hash(key);
	while(data[currentPos].isOccupied==true ){
		if (data[currentPos].key==key) {
			if(data[currentPos].isDeleted==false) 
				return 1;  //key already exists in hashTable
			else{ 
				data[currentPos].isDeleted=false;
				data[currentPos].pv=pv;
				return 0;  //successful insert without rehash
			}
		}
		else{ 
			currentPos++;
			if(currentPos>=capacity)
				currentPos-=capacity;
		}
	}
	data[currentPos].key=key;
	data[currentPos].isOccupied=true;
	data[currentPos].isDeleted=false;
	data[currentPos].pv=pv;
	if(++filled>capacity/2) 
		return ((rehash())?0:2); //rehash and return 0 on success, 2 on failure 
	else
		return 0;  //successful insert without rehash	
}
		
bool hashTable::contains(const string &key){
	return (findPos(key)>=0)?true:false;
}

 void * hashTable::getPointer(const string &key, bool *b){
	//NOT implemented
	return NULL;
}

int hashTable::setPointer(const string &key, void *pv){
	//NOT implemented
	return 0;
}

 bool hashTable::remove(const string &key){
	//NOT implemented
	return true;
}
 
int hashTable::hash(const string &key){
	int hashVal=0;
	for (int i=0;i<key.length();i++)
		hashVal=37*hashVal+key[i];
		
	hashVal%=capacity;
	if(hashVal<0)
		hashVal+=capacity;
		
	return hashVal;
}	
  
int hashTable::findPos(const string &key){
	int currentPos=hash(key);
	while(data[currentPos].isOccupied==true ){
		if (data[currentPos].key==key) 
			return ((data[currentPos].isDeleted==false)?currentPos:-1);  
		else{
			currentPos++;
			if(currentPos>=capacity)
				currentPos-=capacity;
		}
	}
	return -1;
}

bool hashTable::rehash(){
	vector<hashItem>oldData=data;
	int oldCapacity=capacity;
	capacity=getPrime(capacity);
	try{
		data.resize(capacity);
	}
	catch(bad_alloc const&) {
		return false;
	}	
	for(int i=0;i<capacity;i++)
		data[i].isOccupied=false;
	filled=0;
	for(int i=0;i<oldCapacity;i++)
		if(oldData[i].isOccupied==true && oldData[i].isDeleted==false)
			insert(oldData[i].key);
	return true;
	}
	

unsigned int hashTable::getPrime(int size){
	const int primes[17]={24593,49157,98317, 196613, 393241,786433,1572869,3145739,6291469,12582917, 
	                      25165843,50331653,100663319,201326611,402653189,805306457,1610612741};
	for(int i=0;i<17;i++)
		if(primes[i]>size)
			return primes[i];
	cerr<<"Could not resize hashTable! Prime list has expired."<<endl;
	exit(1);
}
