/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #3                                              */
/*                                                                              */ 
/*  graph.cpp                                                                   */
/*                                                                              */
/*  This sourcefile implements all of the data members and member functions of  */
/*  the Graph class defined in graph.h .                                        */
/*                                                                              */
/********************************************************************************/

#include "graph.h"

using namespace std;

Graph::Graph(int size){
	vertex_table=new hashTable(size);
	dijkstra_done=false;
}

Graph::Vertex *Graph::insertVertex(const string &vrtx_id){
	Vertex *vrtx=new Vertex(vrtx_id); // Allocate space for vertex
	vertex_table->insert(vrtx_id,vrtx); // Add vertex to vertex hashtable
	vertex_list.push_back(vrtx); // Add vertex to vertex list
	return vrtx;
}

void Graph::insertEdge(const string &src_id, const string &dest_id, unsigned long weight){
	Vertex *src, *dest;
	// Determine whether src and dest vertices exist. If not create them. Get their memory addresses
	src=(contains(src_id))?(Vertex*)(vertex_table->getPointer(src_id)):insertVertex(src_id);
	dest=(contains(dest_id))?(Vertex*)(vertex_table->getPointer(dest_id)):insertVertex(dest_id);
	// Update Adjaceny list
	(src->adj_list).push_back(Edge(dest,weight));
}  

void Graph::dijkstra(const string &src_id){
	heap Q(vertex_list.size());
	list<Vertex*>::iterator v_itr; //iterator for vertex_list
	list<Edge>::iterator e_itr;    //iterator for adj_list
	const unsigned long INFINITY=2000000000;
	Vertex *v, *w;
	
	//Initialize Heap
	for(v_itr=vertex_list.begin();v_itr!=vertex_list.end();v_itr++ ){
		v=*v_itr;
		v->dist=INFINITY; //dv
		v->known=false; //v_known
		Q.insert(v->id,v->dist,v);
	}
	
	// Set distance of source vertex to 0 in vertex and heap
	v=(Vertex*)vertex_table->getPointer(src_id); // v=*src
	Q.setKey(src_id,v->dist=0); // Set dist of src to 0 in vertex and heap 
	
	// While heap is not empty get (pointer to) unknown vertex,v, w/ min. dist
	while(!Q.deleteMin(NULL,NULL,&v)){ 
		v->known=true; //Make v known
		//Update adjacency list
		for(e_itr=(v->adj_list).begin(); e_itr!=(v->adj_list).end();e_itr++){
			w=e_itr->dest; 
			unsigned long &old_cost=w->dist; // dw
			unsigned long new_cost=v->dist+e_itr->cost; // dv+c_v,w
			if(new_cost<old_cost){
				Q.setKey(w->id,old_cost=new_cost); // Update dist of w in vertex and heap
				w->prev=v;
			}
		}
	}
	dijkstra_done=true;
}

int Graph::printPaths(const string &src_id,ofstream &out){
	if (!dijkstra_done) //dijkstra was not performed
		return 1;
	else{
		list<Vertex*>::iterator v_itr;
		for(v_itr=vertex_list.begin();v_itr!=vertex_list.end();v_itr++ )
			//vertices without paths from source
			if ( ((*v_itr)->prev)==NULL && ((*v_itr)->id)!=src_id )
				out<<(*v_itr)->id<<": NO PATH"<<endl;
			else{ //vertices with paths from source 
				string path;			
				out<<(*v_itr)->id<<": "<<(*v_itr)->dist<<" ["<<printPath(*v_itr,path)<<"]"<<endl;
				}	
		return 0;
	}
}	

std::string &Graph::printPath(const Vertex * dest,std::string &path){
	if ((dest->prev)!=NULL)
		path=printPath(dest->prev,path)+", ";
	path+=dest->id;	
	return path;
}
		 