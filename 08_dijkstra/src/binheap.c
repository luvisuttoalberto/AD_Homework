#include "binheap_no_swap.h"
#include <string.h>
#include <stdio.h>

#define PARENT(node) ((node - 1)/2)
#define LEFT_CHILD(node) (2*(node) + 1)
#define RIGHT_CHILD(node) (2*(node+1))

#define VALID_NODE(H, node) ((H)->num_of_elem>(node))

#define ADDR(H, node) ((H)->A+(((H)->key_pos)[node])*((H)->key_size)) // A[i]
#define INDEX_OF(H, addr) (H)->rev_pos[(((addr-(H)->A))/(H)->key_size)] 

int is_heap_empty(const binheap_type *H)
{
    return H->num_of_elem == 0;
}

const void *min_value(const binheap_type *H)
{
    if (is_heap_empty(H)){
        return NULL;
    }

    // the minimum is stored in the root, a.k.a A[0]
    return ADDR(H, 0);
}

void swap_keys(binheap_type *H, unsigned int n_a, unsigned int n_b)
{
    // swap the positions in key_pos
    // save them to use them when swapping
    // the position in rev_pos
    unsigned int old_position_a = H->key_pos[n_a];
    unsigned int old_position_b = H->key_pos[n_b];
    H->key_pos[n_a] = old_position_b;
    H->key_pos[n_b] = old_position_a;

    // swap the positions in rev_pos
    // using a tmp variable
    unsigned int old_reverse_position_a = H->rev_pos[old_position_a];
    H->rev_pos[old_position_a] = H->rev_pos[old_position_b];
    H->rev_pos[old_position_b] = old_reverse_position_a;
    
}

void heapify(binheap_type * H, unsigned int node)
{
    unsigned int dst_node=node, child;
    do {
        // this is needed for all the successive iteration, first one excluded
        // it's useless for the first iteration
        node = dst_node;

        // find the minimum among node and its children
        // first the right one
        child = RIGHT_CHILD(node);
        if(VALID_NODE(H, child) && H->leq(ADDR(H, child), ADDR(H, dst_node))){
            dst_node = child;
        }
        // then the left one
        child = LEFT_CHILD(node);
        if(VALID_NODE(H, child) && H->leq(ADDR(H, child), ADDR(H, dst_node))){
            dst_node = child;
        }

        // if the minimum is not in node
        // which means it changed in this iteration
        // swap the keys
        if(dst_node != node){
            swap_keys(H, dst_node, node);
        }
    } while(dst_node != node);
}

const void *extract_min(binheap_type *H)
{
    if (is_heap_empty(H)){
        return NULL;
    }

    // swapping the keys of the root (A[0])
    // and the right-most leaf of the
    // last level (A[num_of_elem-1])
    swap_keys(H, 0, H->num_of_elem-1);

    // deleting the right-most leaf of the
    // last level (A[num_of_elem-1])
    // which previously was the root
    H->num_of_elem--;
    
    // increment the number of removed nodes
    H->removed_elem++;

    heapify(H, 0);

    return ADDR(H, H->num_of_elem+1);
}

const void * find_the_max(void *A, 
							const unsigned int num_of_elem,
							const size_t key_size,
							total_order_type leq)
{
	if(num_of_elem == 0){
		return NULL;
	}

	const void *max_value = A;

	// for all the values in A
	for(const void *addr = A + key_size; addr != A + num_of_elem * key_size; addr += key_size){

		// if addr > max_value
		if(!leq(addr, max_value)){
			max_value = addr;
		}
	}
	
	return max_value;
}

binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem,
                         const unsigned int max_size,  
                         const size_t key_size, 
                         total_order_type leq)
{
    
	binheap_type *H = (binheap_type *) malloc(sizeof(binheap_type));

	H->A = A;
	H->num_of_elem = num_of_elem;
	H->max_size = max_size;
	H->key_size = key_size;
	H->leq = leq;
	H->max_order_value = malloc(key_size);
    // in the previous line we are not typecasting the malloc,
    // since max_order_value is a pointer to void.
	// We perform an allocation because the "old" max_order_value
    // might not be available anymore
    H->key_pos = (unsigned int *)malloc(sizeof(unsigned int)*max_size);
    H->rev_pos = (unsigned int *)malloc(sizeof(unsigned int)*max_size);
    H->removed_elem = 0;

	if(num_of_elem == 0){
		return H;
	}

	// get the maximum among A[:num_of_elem-1] (all the elements)
	// and store it in max_order_value
	const void * value = find_the_max(A, num_of_elem, key_size, leq);
	memcpy(H->max_order_value, value, key_size);

    // initialize values in key_pos and rev_pos
    for(unsigned int i = 0; i < num_of_elem; i++){
        H->key_pos[i] = i;
        H->rev_pos[i] = i;
    }

	// fix the heap property from the second last level to the root
	for(unsigned int i = num_of_elem/2; i > 0; i--){
		heapify(H, i);
	}
	heapify(H, 0);

    return H;
}

void delete_heap(binheap_type *H)
{
    free(H->max_order_value);
    free(H->key_pos);
    free(H->rev_pos);
    free(H);
}

const void *decrease_key(binheap_type *H, void *node, const void *value)
{
    unsigned int node_idx = INDEX_OF(H, node);

    // if node doesn't belong to H or *value > *node
    // return NULL
    if(!VALID_NODE(H, node_idx) || !(H->leq(value, node))){
        return NULL;
    }

    memcpy(node, value, H->key_size);
    
    if(node_idx == 0){
        // check on the parent is not needed in this case
        // we've just inserted the first node
        // we can return
        return node;
    }

    unsigned int parent_idx = PARENT(node_idx);
    void *parent = ADDR(H, parent_idx);

    // while node != root and *parent > *node
    while((node_idx != 0) && (!H->leq(parent, node))){

    	// swap parent and node keys
    	swap_keys(H, parent_idx, node_idx);

    	// focus on the node's parent
    	node_idx = parent_idx;
        node = ADDR(H, node_idx);
    	
    	parent_idx = PARENT(node_idx);
        if(node_idx == 0){
            parent_idx = 0;
        }
        parent = ADDR(H, parent_idx);

    }

    return node;
}

const void *insert_value(binheap_type *H, const void *value)
{
    // if the heap is already full
    // return NULL
    if(H->max_size == H->num_of_elem){
    	return NULL;
    }

    // if the new value > *max_order_value
    // change the max_order_value
    if(H->num_of_elem == 0 || !H->leq(value, H->max_order_value)){
        memcpy(H->max_order_value, value, H->key_size);
    }

    // update key_pos
    H->key_pos[H->num_of_elem] = H->num_of_elem + H->removed_elem;

    // update rev_pos
    H->rev_pos[H->num_of_elem + H->removed_elem] = H->num_of_elem;
    
    // get the position of the new node
    void *new_node_addr = ADDR(H, H->num_of_elem);
    
    // assign to the new node the max_order_value
    memcpy(new_node_addr, H->max_order_value, H->key_size);

    // increase the size of the heap
    H->num_of_elem++;

    // decrease the key of the new node
    return decrease_key(H, new_node_addr, value);
}

void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value))
{

    // stores the index of the left-most node of the next level
    unsigned int next_level_node = 1;
    
    for (unsigned int node = 0; node < H->num_of_elem; node++){
        if (node == next_level_node){
            printf("\n");
            next_level_node = LEFT_CHILD(node);
        } else{
            printf("\t");
        }
        key_printer(ADDR(H, node));
    }
    printf("\n");
}