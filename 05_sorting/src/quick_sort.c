#include "quick_sort.h"
#include "swap.h"

#define ADDR(A, j, elem_size) ((A)+(j)*(elem_size))

unsigned int partition(void *A, unsigned int i, unsigned int j, unsigned int p, const size_t elem_size, total_order leq){

    // swap pivot p and first element in A (i)
    swap(ADDR(A, i, elem_size), ADDR(A, p, elem_size), elem_size);
    
    p = i++;
    j--;

    while(i <= j){

        if(!leq(ADDR(A, i, elem_size), ADDR(A, p, elem_size))){

            swap(ADDR(A, i, elem_size), ADDR(A, j, elem_size), elem_size);
            j--;

        }else{
            i++;
        }

    }

    swap(ADDR(A, p, elem_size), ADDR(A, j, elem_size), elem_size);
    return j;
}

void recursive_quick_sort(void *A, unsigned int l, unsigned int r, const size_t elem_size, total_order leq){

    while(l < r){
        unsigned int p = partition(A, l, r, l, elem_size, leq);
        recursive_quick_sort(A, l, p, elem_size, leq);
        l = p + 1;
    }
}

// I use this function just as an api to call the real tail recursive
// implementation of quick sort
void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq)
{
    recursive_quick_sort(A, 0, n, elem_size, leq);
}