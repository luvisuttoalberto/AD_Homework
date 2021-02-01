#include "select.h"
#include "quick_sort.h"
#include "swap.h"

#define ADDR(A, j, elem_size) ((A)+(j)*(elem_size))

int equal_elements(const void *x, const void *y, total_order leq){
    return leq(x, y) && leq(y, x);
}

tuple modified_partition(void *A, unsigned int l, unsigned int r, unsigned int p, const size_t elem_size, total_order leq){
    tuple result;

    // swap pivot p and first element in A (l)
    swap(ADDR(A, l, elem_size), ADDR(A, p, elem_size), elem_size);
    p = l++;
    
    unsigned int num_of_equal_elem = 0;

    while(l <= r){
        if(!equal_elements(ADDR(A, p, elem_size), ADDR(A, l, elem_size), leq)){ // l != p
            if(leq(ADDR(A, l, elem_size), ADDR(A, p, elem_size))){ // l < p
                swap(ADDR(A, l, elem_size), ADDR(A, p - num_of_equal_elem, elem_size), elem_size);
                p = l++;
            }else{ // l > p
                swap(ADDR(A, l, elem_size), ADDR(A, r, elem_size), elem_size);
                r--;
            }
        }else{ // l == p
            p = l++;
            num_of_equal_elem++;
        }
    }

    // final swap
    swap(ADDR(A, p, elem_size), ADDR(A, r, elem_size), elem_size);

    result.first_element = r - num_of_equal_elem;   // end of first section
    result.second_element = r;                      // end of second section

    return result;
}

unsigned int select_pivot(void *A, const unsigned int n, const size_t elem_size, total_order leq){
    
    if(n <= 10){ // base case
        quick_sort(A, n, elem_size, leq);
        return n/2;
    }

    unsigned int num_of_chunks = n/5;

    for(unsigned int i = 0; i < num_of_chunks; i++){
        quick_sort(ADDR(A, i*5, elem_size), 5, elem_size,leq); // sort the single chunk
        // swap the position of the median to be at the beginning of A, to simplify later selection of the median of medians
        unsigned int position_of_the_median = i*5+2;
        swap(ADDR(A, i*5 + 2, elem_size), ADDR(A, i, elem_size), elem_size);
    }

    // find the median of the medians
    return select_index(A, num_of_chunks, num_of_chunks/2, elem_size, leq);
}

unsigned int select_index(void *A, const unsigned int n, const unsigned int i, const size_t elem_size, total_order leq)
{
    if(n <= 10){ // base case
        quick_sort(A, n, elem_size, leq);
        return i;
    }

    unsigned int p = select_pivot(A, n, elem_size, leq);
    tuple indices = modified_partition(A, 0, n-1, p, elem_size, leq);

    if(i < indices.first_element){ // look at the first chunk

        return select_index(A, indices.first_element - 1, i, elem_size, leq);
    
    }else if(i > indices.second_element){ // look at the third chunk
    
        return select_index(ADDR(A, indices.second_element, elem_size), n - 1 - indices.second_element, i, elem_size, leq);
    
    }else{ // we found i, order doesn't matter! All values in the second chunk are equal
    
        return i;
    
    }
}

void recursive_quick_sort_select(void *A, unsigned int l, unsigned int r, const size_t elem_size, total_order leq){

    while(l < r){
        unsigned int p = l + select_pivot(ADDR(A, l, elem_size), r-l, elem_size, leq);

        tuple indeces = modified_partition(A, l, r-1, p, elem_size, leq);
        recursive_quick_sort_select(A, l, indeces.first_element, elem_size, leq);
        l = indeces.second_element + 1;
    }
}

// used just as an API
void quick_sort_select(void *A, const unsigned int n, const size_t elem_size, total_order leq)
{
    recursive_quick_sort_select(A, 0, n, elem_size, leq);
}
