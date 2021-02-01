#include "dijkstra_heap.h"
#include "binheap_no_swap.h"
#include "graph.h"
#include "total_orders_dijkstra.h"
#include <stdio.h>

#define ADDR(H, node) ((H)->A+(((H)->key_pos)[node])*((H)->key_size))

void init_sssp_heap_version(graph * G){

    if(G->number_of_nodes == 0){
        printf("The graph is empty\n");
        return;
    }

    for(unsigned int i = 0; i < G->number_of_nodes; i++){
        G->V[i].distance = INFINITY;
        G->V[i].predecessor = NIL;
    }
}

void update_distance_heap_version(binheap_type * H, const int index, const int new_distance){

    ((vertex *)ADDR(H, index))->distance = new_distance; // G->V[index].distance = new_distance;
    
}

void relax_heap_version(graph * G, binheap_type * H,  const int u, const int v){
    if(G->V[u].distance + G->adjacency_matrix[u][v] < G->V[v].distance){
        
        // update distance
        update_distance_heap_version(H, v, G->V[u].distance + G->adjacency_matrix[u][v]);
        
        // update predecessor
        ((vertex *)ADDR(H, v))->predecessor = u; // G->V[v].predecessor = u;
        
    }
}

void dijkstra_heap(graph * G, const int source){

    // if the graph is empty, avoid the successive computations
    if(G->number_of_nodes == 0){
        printf("The graph is empty\n");
        return;
    }

    // if the source is not valid, return
    if(source >= G->number_of_nodes){
        printf("Selected source is not valid\n");
        return;
    }
    
    // initialization of the Single Source Shortest Path problem
    init_sssp_heap_version(G);
    

    // update distance of the source from itself
    G->V[source].distance = 0;

    // build the heap
    binheap_type * H = build_heap(G->V, G->number_of_nodes, G->number_of_nodes, sizeof(vertex), leq_int_vertex);

    while(!is_heap_empty(H)){

        // take the index of the node that will be extracted
        vertex * node_to_be_extracted = ADDR(H, 0);
        int index_of_node_to_be_extracted = node_to_be_extracted->index;
        
        // for all nodes in the graph
        for(unsigned int i = 0; i < G->number_of_nodes; i++){

            // if there is an edge between the selected node and
            // the other one
            if(G->adjacency_matrix[index_of_node_to_be_extracted][i]!=0){

                // relax on the selected node
                relax_heap_version(G, H, index_of_node_to_be_extracted, i);
            }
        }
        // extract the node from the heap
        extract_min(H);
    }
    delete_heap(H);
    
}

