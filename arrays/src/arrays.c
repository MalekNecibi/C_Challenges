#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"


#include <stdint.h>

#define UNUSED(x) (void)(x)


bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count)
{
    // basic parameter checks
    if (!src || !dst || 0 == elem_size || 0 == elem_count) {
        return false;
    }
    size_t num_bytes = elem_size * elem_count;

    // overlap (undefined behavior)
    if ( src == dst
        || (src < dst && src + num_bytes > dst) 
        || (dst < src && dst + num_bytes > src) ) {
        
        return false;
    }
    
    // explicit cast of unused returns
    (void*)memcpy(dst, src, num_bytes);
    
    return true;
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count)
{
    // basic parameter checks
    if (!data_one || !data_two || 0 == elem_size || 0 == elem_count) {
        return false;
    }
    size_t num_bytes = elem_size * elem_count;

    return ! memcmp(data_one, data_two, num_bytes);
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count)
{
    // basic parameter checks
    if (!data || !target || 0 == elem_size || 0 == elem_count) {
        return -1;
    }
    
    // find index with value `target inside `data` array
    for (size_t i = 0; i < elem_count; i++) {
        
        // &data[i] : need pointer arithmetic b/c arbitrary element width
        const void* data_i = data + (i * elem_size);
        
        // target match found!
        if (0 == memcmp(data_i, target, elem_size)) {
            return i;
        }
    }
    
    return -1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count)
{
    // basic param checks
    if (!src_data || !dst_file || 0 == elem_size || 0 == elem_count) {
        return false;
    }

    // don't allow newlines in filenames
    char* newline_index = strchr(dst_file, '\n');
    if (newline_index) {
        return false;
    }
    
    FILE *fp = fopen(dst_file, "wb");
    if (!fp) {
        //printf("ERROR : Invalid destination file '%s'\n", dst_file);
        return false;
    }
    
    // deserialize, ensure everything was written
    size_t elem_written = fwrite(src_data, elem_size, elem_count, fp);
    
    fclose(fp);
    return (elem_written == elem_count);
}

// TODO : read to temporary data and copy only if everything succeeds
//      : currently dst_data corrupted if deserialize operation fails prematurely
bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count)
{
    // basic param checks
    if (!src_file || !dst_data || 0 == elem_size || 0 == elem_count) {
        return false;
    }
    
    // don't allow newlines in filenames
    char* newline_index = strchr(src_file, '\n');
    if (newline_index) {
        return false;
    }
    
    FILE *fp = fopen(src_file, "rb");
    if (!fp) {
        //printf("ERROR : Invalid source file '%s'\n", src_file);
        return false;
    }
    
    // deserialize, ensure everything was read in
    size_t elem_read = fread(dst_data, elem_size, elem_count, fp);
    
    fclose(fp);
    return (elem_read == elem_count);
}

