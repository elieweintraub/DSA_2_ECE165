/********************************************************************************/
/*  Elie Weintraub                                                             */
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
}

int heap::insert(const std::string &id, int key, void *pv){
	if(currentSize>=capacity)
		return 1; // heap is already filled to capacity
	else if(mapping->contains(id)==1) 
		return 2; // node with given id already exists
	else{
		data[++currentSize].key=key;
		data[currentSize].id=id;
		data[currentSize].pData=pv;
		mapping->insert(id,&data[currentSize]);
		percolateUp(currentSize);
		return 0; //successful insert
	}
}

int heap::setKey(const std::string &id, int key){
	bool exists;
	int posCur;
	node *pn=static_cast<node*> (mapping->getPointer(id,&exists));
	if (exists==false)
		return 1; // node with the given id does not exist
	else{
		int oldKey=data[posCur=getPos(pn)].key;
		data[posCur].key=key;
		if(oldKey<key)
			percolateDown(posCur);
		else if(oldKey>key)
			percolateUp(posCur);
		return 0;
	}
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	if(currentSize<=0)
		return 1; //the heap is empty
	else{ 
		if(mapping->remove(data[1].id)==false)   
			cerr<<"remove shouldn't return false"<<endl; 
		if(pId!=NULL)
			*pId=data[1].id;
		if(pKey!=NULL)
			*pKey=data[1].key;
		if(ppData!=NULL)
			*(static_cast<void **>(ppData))=data[1].pData;
		data[1]=data[currentSize--];	
		mapping->setPointer(data[1].id,&data[1]);
		percolateDown(1);
		return 0;
	}
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
	bool exists;
	node *pn=static_cast<node*> (mapping->getPointer(id,&exists));
	if (exists==false)
		return 1; // node with the given id does not exist
	else{
		int posCur=getPos(pn);
		int oldKey=data[posCur].key;
		if(pKey!=NULL)
			*pKey=oldKey;
		if(ppData!=NULL)
			*(static_cast<void **>(ppData))=data[posCur].pData;
		if(mapping->remove(data[posCur].id)==false)   
			cerr<<"remove shouldn't return false"<<endl; 	
		data[posCur]=data[currentSize--];
		mapping->setPointer(data[posCur].id,&data[posCur]);
		if(oldKey<data[posCur].key)
			percolateDown(posCur);
		else if(oldKey>data[posCur].key)
			percolateUp(posCur);
		return 0;		
	}
}

void heap::percolateUp(int posCur){
	int posHole=posCur; 
	node tmp=data[posCur];
	
	for(;posHole>1 &&tmp.key<data[posHole/2].key;posHole/=2){
		data[posHole]=data[posHole/2];
		mapping->setPointer(data[posHole].id,&data[posHole]);
	}
	data[posHole]=tmp;
	mapping->setPointer(tmp.id,&data[posHole]);
}

void heap::percolateDown(int posCur){
	int posHole=posCur;
	int posChild;
	node tmp=data[posCur];
	
	for(;posHole*2<=currentSize;posHole=posChild){
		posChild=posHole*2;
		if(posChild!=currentSize && data[posChild+1].key<data[posChild].key)
			posChild++;
		if(data[posChild].key<tmp.key){
			data[posHole]=data[posChild];
			mapping->setPointer(data[posHole].id,&data[posHole]);
		}
		else
			break;
	}
	data[posHole]=tmp;
	mapping->setPointer(tmp.id,&data[posHole]);
}

int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

