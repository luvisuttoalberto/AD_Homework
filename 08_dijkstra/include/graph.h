#ifndef __GRAPH__
#define __GRAPH__

#include <stdlib.h> //for rand()

typedef struct vertex{
    
    unsigned int index;
    unsigned int distance;
    int predecessor; // int in order to assign in init_sssp NIL=-1

}vertex;


/** 
 * @struct graph
 * @brief A struct that represents graphs.
 *  
 * This struct is meant to represent graphs.
 * It is implemented with an adjacency matrix.
 */
typedef struct graph{
    unsigned int number_of_nodes; // This is the number of nodes in the graph
    vertex * V; // This is the array of vertices
    int ** adjacency_matrix; // This is the adjacency matrix of the graph
}graph;

/** 
 * Build a new graph.
 * 
 * This function builds a new graph and fills the adjacency matrix
 * by using random generated weights.
 * 
 * @param number_of_nodes is the number of nodes in the graph.
 * @return a pointer to the new graph.
 */
graph * build_graph(unsigned int number_of_nodes);


/**
 * Destroy a graph.
 * 
 * This function releases the memory space required to represent a graph.
 * 
 * @param G is the graph that will be destroyed.
 */
void delete_graph(graph * G);

#endif //__GRAPH__