#include "../include/debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// protected function, that only this .c can use
int comparator_func(const void *a, const void *b) {
    return *(uint16_t*)a - *(uint16_t*)b;
}

bool terrible_sort(uint16_t *data_array, const size_t value_count) {
    if (!data_array || 0 == value_count) {
        return false;
    }
    
    size_t num_bytes = value_count * sizeof(uint16_t);
    
    // Clone dataset for sort, prevent corruption
    uint16_t* sorting_array = malloc(num_bytes);
    if (!sorting_array) {
        return false;
    }
    
    // Copy to the Clone
    // keeping manual comparison bc spirit of this challenge
    // memcpy(sorting_array, data_array, num_bytes);
    for (size_t i = 0; i < value_count; i++) {
        sorting_array[i] = data_array[i];
    }
    
    // Perform sort
    qsort(sorting_array, value_count, sizeof(uint16_t), comparator_func);

    // Test if sort succeeded
    bool sorted = true;
    for (size_t i = 0; i < value_count-1; i++) {
        sorted = sorted && (sorting_array[i] <= sorting_array[i + 1]);
    }
    
    // commit the changes
    if (sorted) {
        memcpy(data_array, sorting_array, num_bytes);
    }

    free(sorting_array);
    return sorted;
}

