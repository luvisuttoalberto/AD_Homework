#include "test.h"
#include "graph.h"

double test(void (*f)(graph *, int), graph * G, int source){
    struct timespec requestStart, requestEnd;
    double accum;
    unsigned int rep = 50;
    
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for(unsigned int i = 0; i < rep; i++){
        f(G, source);
    }

    clock_gettime(CLOCK_REALTIME, &requestEnd);
    accum = (requestEnd.tv_sec - requestStart.tv_sec)+(requestEnd.tv_nsec - requestStart.tv_nsec)/1E9;
    return accum/rep;
    
}
