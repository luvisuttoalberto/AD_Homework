#ifndef __TEST__
#define __TEST__

#include <time.h>
#include "graph.h"
#include "dijkstra_array.h"

double test(void (*f)(graph *, int), graph * G, int source);

#endif