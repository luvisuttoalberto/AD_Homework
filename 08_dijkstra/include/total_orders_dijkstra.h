#ifndef __TOTAL_ORDERS_DIJKSTRA__
#define __TOTAL_ORDERS_DIJKSTRA__

typedef int (*total_order_type)(const void *a, const void *b);

int leq_float(const void *a, const void *b);
int leq_int(const void *a, const void *b);
int geq_int(const void *a, const void *b);
int leq_int_vertex(const void *a, const void *b);


#endif