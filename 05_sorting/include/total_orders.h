#ifndef __TOTAL_ORDERS__
#define __TOTAL_ORDERS__

typedef int (*total_order_type)(const void *a, const void *b);

int leq_float_bin_heap(const void *a, const void *b);
int leq_int_bin_heap(const void *a, const void *b);
int geq_int_bin_heap(const void *a, const void *b);

#endif