/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #3                                              */
/*                                                                              */ 
/*  graph.h                                                                     */
/*                                                                              */
/*  This headerfile defines all of the data members and member functions of     */
/*  a Graph class.                                                              */
/*                                                                              */
/********************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include <fstream>

#include "heap.h"
#include "hash.h"

class Graph{
 public:

  // The constructor initializes the Graph. Takes a parameter size for vertex_table, the 
  // data member of the Graph that stores the vertices in a hashTable for quick lookup.
  // Initiializes dijkstra_done to false to indicate dijkstra has not been performed yet. 
  Graph(int size=0);  
  
  // Takes 2 vertex ids, 1 for the source and the other for the destination,
  // as well as the weight of the edge and then constructs the edge. 
  //Uses the helper function insertVertex. 
  void insertEdge(const std::string &src_id, const std::string &dest_id, unsigned long weight);
  
  // Performs Dijksra's shortest path algorithm and sets dijkstra_done bool to true to indicate
  // that dijkstra has been performed.
  void dijkstra(const std::string &src_id);  
  
  // Prints the shortest path from the source vertex to every other vertex in the graph.
  // If no path exists this is indicated. 
  // Also, checks to ensure dijkstra's algorithm has been performed and so a source vertex is defined.
  // Returns 0 on success. 1 on Failure. Uses helper function printPath.
  int printPaths(const std::string &src_id, std::ofstream &out);
 
  // Check if the specified vertex is in the Graph.
  // If so, return true; otherwise, return false.
  bool contains(const std::string &vrtx_id){return vertex_table->contains(vrtx_id);}
  
 private:
 
 //Private nested classes:
  
  class Edge;
  // Vertex is a nested class within Graph. 
  // The vertex_list member of the Graph class stores vertices. 
  class Vertex{
   public:
    std::string id; // vertex id
	std::list<Edge> adj_list;  //list of edges that are incident on the given vertex
	// The next three data members are used in dijkstra's algorithm.
	bool known; // True if the given vertex is in the known set. False otherwise.
	unsigned long dist; // The distance of the current path from src to the given vertex.
	Vertex *prev; // Pntr to the prv vertex in the curr path from src to given vertex.
	//Vertex Constructor
	Vertex(const std::string &name, Vertex *pv=NULL):id(name), prev(pv){};
  };
	 
  // Edge is a nested class within Graph.
  // The adjacency list member, adj_list, of each vertex stores edges incident on the vertex.	 
  class Edge{
   public:
    unsigned long cost; // Cost of the given edge.
    Vertex * dest; // Pointer to the destination vertex of the given edge.
	// Edge constructor
	Edge( Vertex *dest_ptr, int weight): dest(dest_ptr), cost(weight){}; 
  };
  
  //Private data members:
  
  std::list<Vertex*> vertex_list; // List of vertices in the graph
  hashTable *vertex_table; // Hashtable of vertices in the graph. 
  bool dijkstra_done; //flag for whether or not Dijkstra's algorithm was performed
  
  //Private helper functions:
  
  // Takes vertex id and inserts the vertex into the graph.
  // Used as helper function for insertEdge. 
  // Returns address of the created vertex
  Vertex *insertVertex(const std::string &vrtx_id);
  
  
  // Prints (to a string) the shortest path from the source vertex 
  // to the given destination vertex. Assumes that a path exists.
  // Complete formatting is done only in printPaths. This is meant to be 
  // used only as a helper function for printPaths.
  std::string &printPath(const Vertex *dest, std::string &path);
};

#endif //_GRAPH_H	