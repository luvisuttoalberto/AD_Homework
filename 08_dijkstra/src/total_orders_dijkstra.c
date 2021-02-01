#include <stdlib.h>
#include "total_orders_dijkstra.h"
#include "graph.h"

int leq_float(const void *a, const void *b)
{
  return *((float*)a)<=*((float*)b);
}

int leq_int(const void *a, const void *b)
{
  return *((int*)a)<=*((int*)b);
}

int geq_int(const void *a, const void *b)
{
  return *((int*)a)>=*((int*)b);
}

int leq_int_vertex(const void *a, const void *b)
{
  vertex * tmp_a = (vertex*) a;
  vertex * tmp_b = (vertex*) b;
  return leq_int((void*)&tmp_a->distance, (void*)&tmp_b->distance);
}