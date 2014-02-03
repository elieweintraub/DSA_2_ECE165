/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #2                                              */
/*                                                                              */ 
/*  heap.cpp                                                                    */
/*                                                                              */
/*  This sourcefile implements all of data members and member functions of      */
/*  the heap class defined in heap.h .                                          */
/*                                                                              */
/********************************************************************************/

#include <iostream>
#include <cstdlib>

#include "heap.h"

using namespace std;

heap::heap(int size):currentSize(0),capacity(size){
	data.resize(capacity+1);
	mapping = new hashTable(capacity*2);
	//not finished implementing
}

int heap::insert(const std::string &id, int key, void *pv){
	//NOT implemented
	return 0;
}

int heap::setKey(const std::string &id, int key){
	//NOT implemented
	return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	//NOT implemented
	return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
	//NOT implemented
	return 0;
}

void heap::percolateUp(int posCur){
	for(int posHole=posCur;posHole>1 && data[posHole].key<data[posHole/2].key;posHole/=2){
		data[posHole].id=data[posHole/2].id;
		data[posHole].key=data[posHole/2].key;
		data[posHole].pData=data[posHole/2].pData;
	}
	data[posHole].id=data[posCur].id;
	data[posHole].key=data[posCur].key;
	data[posHole].pData=data[posCur].pData;
//	//NOT implemented
}

void heap::percolateDown(int posCur){
	//NOT implemented
}

int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

