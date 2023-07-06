#include "../include/structures.h"
#include <stdio.h>

int compare_structs(sample_t* a, sample_t* b)
{
    // basic parameter checking
    if (!a || !b) {
        return 0;
    }
    
    // boolean, initially assume they match
    int equal = 1;
    
    // only update if they don't match
    equal = equal && (a->a == b->a);
    equal = equal && (a->b == b->b);
    equal = equal && (a->c == b->c);

    // force cast to 0 or 1 (redundant, but potentially undefined behavior)
    return equal ? 1 : 0;
}

// unused, instructional aide
void print_alignments()
{
	printf("Alignment of int is %zu bytes\n",__alignof__(int));
	printf("Alignment of double is %zu bytes\n",__alignof__(double));
	printf("Alignment of float is %zu bytes\n",__alignof__(float));
	printf("Alignment of char is %zu bytes\n",__alignof__(char));
	printf("Alignment of long long is %zu bytes\n",__alignof__(long long));
	printf("Alignment of short is %zu bytes\n",__alignof__(short));
	printf("Alignment of structs are %zu bytes\n",__alignof__(fruit_t));
}


// better name: count_fruit_types()
int sort_fruit(const fruit_t* a,int* apples,int* oranges, const size_t size)
{
    // basic parameter checking
    if (!a || !apples || !oranges || 0 == size) {
        return -1;
    }
    
    // initialize the counters
	*apples = 0;
    *oranges = 0;
    
    // mark counters according to type
    for (size_t i = 0; i < size; i++) {
        if (a[i].type == APPLE) {
            (*apples)++;
        
        } else if (a[i].type == ORANGE) {
            (*oranges)++;
        
        } else {
            //printf("[%zu] neither type of fruit?? : %d\n", i, a[i].type);
        }
    }
    
    // TODO : what if apples + oranges != size?
    // return *apples + *oranges;
    return size;
}

int initialize_array(fruit_t* a, int apples, int oranges)
{
    // basic parameter checking
    if (!a || apples < 0 || oranges < 0 || apples + oranges <= 0) {
        return -1;
    }
    
    // initialize all the apples
    for (int i = 0; i < apples; i++) {
        a[i].type = APPLE;
    }
    
    // initialize all the oranges, starting after the apples
    for (int i = apples; i < apples + oranges; i++) {
        a[i].type = ORANGE;
    }
	
    return 0;
}

int initialize_orange(orange_t* a)
{
	// basic parameter checking
    if (!a) {
        return -1;
    }

    // perform initialization (mark type)
    a->type = ORANGE;
    return 0;

}

int initialize_apple(apple_t* a)
{
	// basic parameter checking
	if (!a) {
        return -1;
    }

    // perform initialization (mark type)
    a->type = APPLE;
    return 0;
}
