#ifndef __DIJKSTRA_HEAP__
#define __DIJKSTRA_HEAP__

#include <binheap_no_swap.h>
#include "graph.h"

#define INFINITY 1000000000
#define NIL -1

/**
 * Initialization of the single source shortest path problem.
 *  
 * This function sets, for each vertex of the graph, all distances to
 * INFINITY and all predecessors to NIL.
 * 
 * @param G is the graph to which the vertices belongs.
 */
void init_sssp_heap_version(graph * G);

/**
 * Update of the candidate distance from the source.
 * 
 * This function updates the candidate distance from the source of a given
 * node. Auxiliary function for the relax method.
 * 
 * @param H heap that contains the queue with the nodes to be updated.
 * @param index of the node whose distance will be updated.
 * @param new_distance new value of the candidate distance.
 */
void update_distance_heap_version(binheap_type * H, const int index, const int new_distance);

/**
 * Relax function for the candidate distances from the source.
 * 
 * This function updates the candidate distance and predecessor of a node
 * in vector V of graph G, when necessary. It uses the heap queue to 
 * access the values in V.
 * 
 * @param G graph containing the vector of vertices.
 * @param H heap that contains the queue with the nodes to be updated.
 * @param u candidate predecessor for node v.
 * @param v node whose distance and predecessor could be updated.
 */
void relax_heap_version(graph * G, binheap_type * H, const int u, const int v);

/**
 * Execution of the Dijkstra algorithm in the heap version for the single
 * source shortest path problem.
 * 
 * This function performs the execution modifying the values of vector
 * of vertices V, member of the struct graph.
 * 
 * @param G is the graph involved in the execution.
 * @param source is the source node for the algorithm.
 */
void dijkstra_heap(graph * G, const int source);

#endif