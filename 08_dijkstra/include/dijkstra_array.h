#ifndef __DIJKSTRA_ARRAY__
#define __DIJKSTRA_ARRAY__

#include "graph.h"

#define INFINITY 1000000000
#define NIL -1

typedef struct queue{
    int * array;
    unsigned int size;
}queue;


/**
 * Initialization of the queue.
 * 
 * This function initializes the queue, adding all nodes
 * to the queue.array member, according to the size.
 * 
 * @param size of the queue.
 */
queue * build_queue(unsigned int size);

/**
 * Check on the dimension of the queue.
 * 
 * This function checks if the queue is empty.
 * 
 * @param Q queue to be checked.
 */
int is_empty(queue * Q);

/**
 * Swapping of two elements in the queue.
 * 
 * This function is an auxiliary method used by the extract_min
 * function to swap two elements in the queue.
 * 
 * @param Q queue that contains the two nodes to be swapped.
 * @param node_a first node to be swapped.
 * @param node_b second node to be swapped.
 */
void swap(queue * Q, unsigned int node_a, unsigned int node_b);

/**
 * Extraction of the node with minimum distance from the queue.
 * 
 * This function extract the node with minimum candidate distance
 * from the queue, using the auxiliary function swap to put the 
 * selected node at the end of the queue and reducing the queue size.
 * 
 * @param G graph that contains the vector of vertices with the respective candidate distances
 * @param Q queue that contains the nodes
 * @return the index of the queue that contains the extracted value.
 */
int extract_min_queue(graph * G, queue * Q); //maybe const int const * distance???

/**
 * Update of the candidate distance from the source.
 * 
 * This function updates the candidate distance from the source of a given 
 * node. Auxiliary function for the relax method.  
 * 
 * @param G graph that contains the nodes.
 * @param index of the node whose distance will be updated.
 * @param new_distance new value of the candidate distance.
 */
void update_distance(graph * G, const int index, int new_distance);

/**
 * Relax function for the candidate distances from the source.
 * 
 * This function updates the distance and predecessor of a node 
 * in vector V of graph G, when necessary.
 * 
 * @param G graph containing the vector of vertices.
 * @param u candidate predecessor for node v.
 * @param v node whose distance and predecessor could be updated.
 */
void relax(graph * G, const int u, const int v);

/**
 * Initialization of the single source shortest path problem.
 * 
 * This function sets, for each vertex of the graph,
 * all distances to INFINITY and all predecessors to NIL.
 * 
 * @param G is the graph to which the vertices belongs.
 */
void init_sssp(graph * G);


/**
 * Execution of the Dijkstra algorithm for the single
 * source shortest path problem.
 * 
 * This function performs the execution modifying the values
 * of vector of vertices V, member of the struct graph.
 * 
 * @param G is the graph involved in the execution.
 * @param source is the source node for the algorithm.
 */
void dijkstra_array(graph * G, int source);

#endif