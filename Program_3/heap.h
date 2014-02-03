/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #2                                              */
/*                                                                              */ 
/*  heap.h                                                                      */
/*                                                                              */
/*  This headerfile defines all of data members and member functions of         */
/*  a heap class.                                                               */
/*                                                                              */
/********************************************************************************/

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>

#include "hash.h"

class heap {

 public:
 
  //Public member functions of the heap class:
 
  //
  // heap - The constructor allocates space for the nodes of the heap
  // and the mapping (hash table) based on the specified capacity
  //
  heap(int size);

  //
  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
  //
  int insert(const std::string &id, int key, void *pv = NULL);

  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int setKey(const std::string &id, int key);

  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not NULL), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //
  int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

  //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

 private:
  
  // A nested class within heap:
  class node {
  public:
    std::string id; // The id of this node
    int key; // The key of this node
    void *pData; // A pointer to the actual data
  };
  
  // Private data members of the heap class:
  int capacity; // the capacity of the heap
  int currentSize; // the current size of the heap
  std::vector<node> data; // The actual binary heap
  hashTable *mapping; // maps ids to node pointers

  // Private member functions of the heap class:
  
  //
  // percolateUp - used to preserve the heap ordering principle.
  //
  // Takes posCur as the initiial position of the hole and slides it up the heap until
  // the node could be inserted into the hole without violating the ordering principle.
  // Used as a helper function for insert, remove, and setKey.
  //
  void percolateUp(int posCur); 

  //
  // percolateDown - used to preserve the heap ordering principle.
  //
  // Takes posCur as the initiial position of the hole and slides it down the heap until
  // the node could be inserted into the hole without violating the ordering principle.
  // Used as a helper function for remove, setKey, and deleteMin.
  //
  void percolateDown(int posCur);
  
  //
  // getPos- gets the index of a node in the data vector given a pointer to node
  //
  // Takes a pointer to node and returns the index of the pointed to node in the data vector.
  // Used as a helper function in setKey and remove.
  //
  int getPos(node *pn);

};

#endif //_HEAP_H
