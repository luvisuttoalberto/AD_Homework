#include "insertion_sort.h"
#include "swap.h"

#define ADDR(A, j, elem_size) ((A)+(j)*(elem_size))

void insertion_sort(void *A, const unsigned int n, const size_t elem_size, total_order leq)
{
    for(unsigned int i = 1; i < n; i++){

        unsigned int j = i;

        while(j > 0 && leq(ADDR(A, j, elem_size), ADDR(A, j-1, elem_size))){
            swap(ADDR(A, j-1, elem_size), ADDR(A, j, elem_size), elem_size);
            j--;
        }
    }
}