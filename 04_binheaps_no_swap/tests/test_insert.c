#include <stdio.h>
#include <string.h>
#include "binheap_no_swap.h"

#include "common/test_time.h"

#define MAX_SIZE 30

void int_printer(const void *value)
{
  printf("%d", *((const int *)value));
}

int main(int argc, char *argv[])
{	
  float *maxA=(float *)malloc(sizeof(int)*MAX_SIZE);
  binheap_type *maxH=build_heap_no_swap_version(maxA,0,MAX_SIZE,sizeof(int),geq_int);

  float *minA=(float *)malloc(sizeof(int)*MAX_SIZE);
  binheap_type *minH=build_heap_no_swap_version(minA,0,MAX_SIZE,sizeof(int),leq_int);
  
  printf("Keep inserting and removing the minimum from the (min/max)heaps ");
  printf("until they are\nnot empty.\n\n");
  int value;
  do {
    printf("Insert an integer number (0 to extract the min): ");
    scanf("%d", &value);

    if (value != 0) {
      insert_value_no_swap_version(maxH, &value);
      insert_value_no_swap_version(minH, &value);
    } else {
      extract_min_no_swap_version(maxH);
      extract_min_no_swap_version(minH);
    }

    printf("Max Heap\n");
    print_heap_no_swap_version(maxH, int_printer);

    printf("\nMin Heap\n");
    print_heap_no_swap_version(minH, int_printer);
    printf("\n");

  } while (!is_heap_empty_no_swap_version(minH));
  
  delete_heap_no_swap_version(minH);
  delete_heap_no_swap_version(maxH);

  free(minA);
  free(maxA);
  
  return 0;
}

