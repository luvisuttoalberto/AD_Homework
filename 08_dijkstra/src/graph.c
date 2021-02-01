#include "graph.h"

#define MAX_NUM_OF_NEIGH_PER_NODE 10    // Maximum number of neighbours per node 
#define MAX_WEIGHT 10                   // Maximum weight of an edge

graph * build_graph(unsigned int number_of_nodes){

    graph * G = (graph *) malloc(sizeof(graph));

    G->number_of_nodes = number_of_nodes;
    G->V = (vertex*)malloc(number_of_nodes * sizeof(vertex));
    G->adjacency_matrix = (int**)malloc(number_of_nodes * sizeof(int*));

    for(unsigned int i = 0; i < number_of_nodes; i++){
        G->adjacency_matrix[i] = (int*)calloc(number_of_nodes, sizeof(int));
    }

    if(number_of_nodes == 0){
        return G;
    }

    for(unsigned int i = 0; i < number_of_nodes; i++){
        G->V[i].index = i;
    }

    // initialization of the adjacency matrix
    for(unsigned int i = 0; i < number_of_nodes; i++){

        // pick the number of neighbours for node i
        int number_of_neigh = rand()%MAX_NUM_OF_NEIGH_PER_NODE;
        
        // add neighbours to the adjacency matrix
        while(number_of_neigh > 0){

            // pick the neighbour randomly
            int neighbour = rand()%number_of_nodes;


            // update the weight of the edge.
            // weight must be more than 0; that's why we add 1
            // if it's 0 we don't have an edge
            G->adjacency_matrix[i][neighbour] = rand()%MAX_WEIGHT + 1; 
            number_of_neigh--;

        }
    }

    return G;
}

void delete_graph(graph * G){

    for(unsigned int i = 0; i < G->number_of_nodes; i++){
        free(G->adjacency_matrix[i]);
    }
    free(G->adjacency_matrix);
    free(G->V);
    free(G);
    
}