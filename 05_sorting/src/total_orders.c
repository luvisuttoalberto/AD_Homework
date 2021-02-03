#include <stdlib.h>
#include "total_orders.h"

int leq_float_bin_heap(const void *a, const void *b)
{
  return *((float*)a)<=*((float*)b);
}

int leq_int_bin_heap(const void *a, const void *b)
{
  return *((int*)a)<=*((int*)b);
}

int geq_int_bin_heap(const void *a, const void *b)
{
  return *((int*)a)>=*((int*)b);
}