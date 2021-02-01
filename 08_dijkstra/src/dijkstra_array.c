#include "dijkstra_array.h"
#include <stdio.h> //print

queue * build_queue(unsigned int size){
    queue * Q = (queue *) malloc(sizeof(queue));

    Q->array = (int *)malloc(sizeof(int)*size);
    Q->size = size;

    for(int i = 0; i < size; i++){
        Q->array[i] = i;
    }

    return Q;
}

int is_empty(queue * Q){
    return Q->size == 0;
}

void swap(queue * Q, unsigned int node_a, unsigned int node_b){
    unsigned int tmp = Q->array[node_a];
    Q->array[node_a] = Q->array[node_b];
    Q->array[node_b] = tmp;
}

int extract_min_queue(graph * G, queue * Q){
    // not necessary to perform a check on the emptyness
    // of the queue, if we call this function we are sure
    // it is not empty.

    unsigned int idx_min = 0;

    for(int i = 1; i < Q->size; i++){
        if(G->V[Q->array[i]].distance < G->V[Q->array[idx_min]].distance){
            idx_min = i;
        }
    }

    swap(Q, Q->size - 1, idx_min);
    Q->size--;

    return Q->size;
}

void init_sssp(graph * G){

    if(G->number_of_nodes == 0){
        return;
    }

    for(unsigned int i = 0; i < G->number_of_nodes; i++){
        G->V[i].distance = INFINITY;
        G->V[i].predecessor = NIL;
    }
}

void update_distance(graph * G, const int index, const int new_distance){
    G->V[index].distance = new_distance;
}

void relax(graph * G, const int u, const int v){
    if(G->V[u].distance + G->adjacency_matrix[u][v] < G->V[v].distance){
        
        // update distance
        update_distance(G, v, G->V[u].distance + G->adjacency_matrix[u][v]);
        
        // update predecessor
        G->V[v].predecessor = u;
    }
}

void dijkstra_array(graph * G, const int source){

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
    init_sssp(G);

    // update distance of the source from itself
    G->V[source].distance = 0;

    // build the queue
    queue * Q = build_queue(G->number_of_nodes);

    while(!is_empty(Q)){

        // extract the node from the queue
        int extracted_node = Q->array[extract_min_queue(G, Q)];

        // for all nodes in the graph
        for(unsigned int i = 0; i < G->number_of_nodes; i++){

            // if there is an edge between the extracted node and
            // the other one
            if(G->adjacency_matrix[extracted_node][i]!=0){

                // relax on the extracted node
                relax(G, extracted_node, i);
            }
        }
    }
}