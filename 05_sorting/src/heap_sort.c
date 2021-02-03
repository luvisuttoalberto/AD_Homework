#include "heap_sort.h"
#include "binheap.h"

#define ADDR(A, j, elem_size) ((A)+(j)*(elem_size))

void heap_sort(void *A, const unsigned int n, const size_t elem_size, total_order leq)
{
    // building a max heap
    binheap_type * H = build_heap(A, n, n, elem_size, geq_int);
    
    // extracting the min (which is the maximum value, since we have built a max heap)
    // in this way, in the end the array is already ordered
    for(unsigned int i = 0; i < n; i++){
        extract_min(H);
    }
}