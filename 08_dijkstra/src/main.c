#include "graph.h"
#include "dijkstra_array.h"
#include "test.h"
#include "dijkstra_heap.h"
#include <stdio.h> // printf

int main(int argc, char * argv[]){

    int source = 0;

    // uncomment the following section if you want to test the 
    // algorithm with a small graph and print out, in the end,
    // the problem solved.
    
    /*
    unsigned int number_of_nodes = 10;
    graph * G = build_graph(number_of_nodes);

    printf("%f\n", test(dijkstra_heap, G, source));

    for(unsigned int i = 0; i < number_of_nodes; i++){
        printf("node: %d, distance: %d, predecessor: %d\n", i, G->V[i].distance, G->V[i].predecessor);
    }

    delete_graph(G);
    */

    unsigned int n = (1 << 15);

    printf("Size\tArray\t\tHeap\n");
    for(unsigned int j = 16; j <= n; j *= 2){
        graph * G = build_graph(j);
        printf("%d\t%f\t%f\n", j, test(dijkstra_array, G, source), test(dijkstra_heap, G, source));
        delete_graph(G);
    }

    return 0;
}