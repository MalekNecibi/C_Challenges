#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// #include <string.h>
#include "../include/system_programming.h"

#define UNUSED(x) (void)(x)

const size_t FILENAME_MAX_LENGTH = 64;
const char*  FILENAME_ILLEGAL_CHARS = "#%&{}<>*?/$!':@\"\\\r\n\t";

// used in `endianess_converter`
// arguably undefined behavior, but very common in practice
union Word {
    uint32_t word;
    uint8_t bytes[ sizeof(uint32_t) / sizeof(uint8_t) ];    // 4
};


// File Descriptors only (FILE* not allowed)

bool legal_filename(const char *filename) {
    // basic parameter validation
    if (!filename
    || '\0' == filename[0]) {
        return false;
    }

    // maximum length
    if ( strlen(filename) > FILENAME_MAX_LENGTH ) {
        return false;
    }

    // ban illegal special characters
    if ( '\0' == filename[strspn(filename, FILENAME_ILLEGAL_CHARS)] ) {
        return false;
    }
    
    return true;
}



bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size)
{
    // basic parameter validation
    if (!input_filename
    || !dst
    || 0 == dst_size
    || !legal_filename(input_filename) ) {
        return false;
    }

    // Try opening the given filepath
    int fd = open(input_filename, O_RDONLY);
    if (fd < 0) {
        // printf("ERROR : failed to open provided file '%s'\n", input_filename);
        return false;
    }
    
    // skip first `offset` bytes from start of file
    lseek(fd, offset, SEEK_SET);

    // read in the target data
    size_t bytes_read = read(fd, dst, dst_size);
    if (bytes_read != dst_size) {
        // if dst buffer is corrupted, caller needs to know
        return false;
    }
    
    // cleanup for exit
    (void)close(fd);

    return true; 
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size)
{
    // basic parameter validation
    if (!src
    || !output_filename
    || 0 == src_size
    || !legal_filename(output_filename) ) {
        return false;
    }
    
    // open and prepare file for writing
    int fd = open(output_filename, O_RDWR);
    if (fd < 0) {
        // printf("ERROR : failed to open provided file '%s'\n", output_filename);
        return false;
    }
    
    // skip first `offset` bytes from start of file
    lseek(fd, offset, SEEK_SET);

    // write data to file
    ssize_t bytes_written = write(fd, src, src_size);

    // ensure everything worked properly
    if (bytes_written < 0 || (size_t)bytes_written != src_size) {
        return false;
    }
    
    // cleanup for exit
    (void)close(fd);

    return true;
}


bool file_stat(const char *query_filename, struct stat *metadata)
{
    if (!query_filename
    || !metadata
    || !legal_filename(query_filename) ) {
        return false;
    }
    
    int fd = open(query_filename, O_RDONLY);
    if (fd < 0) {
        // printf("ERROR : failed to open provided file '%s'\n", query_filename);
        return false;
    }
    
    if (-1 == fstat(fd, metadata)) {
        return false;
    }

    return true;
}


bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count)
{
    if (!src_data
    || !dst_data
    || 0 == src_count) {
        return false;
    }
    
    // approach : loop through and swap bytes from source to destination (for readability)
    // alternative : chaining AND-masked bit shifts
    // dst_data[i] = ((src_data[i] >> 24) & 0x000000FF) | ...

    union Word src;
    src.word = 0;

    union Word dst;
    dst.word = 0;
    
    int num_bytes = sizeof(uint32_t) / sizeof(uint8_t); // 4

    // endianess affects discrete (n-byte) words
    for (size_t i = 0; i < src_count; i++) {
        src.word = src_data[i];
        
        // for each byte in word
        for (int j = 0; j < num_bytes; j++) {
            // mirror leading and trailing bytes (0->3 ... 3->0)
            dst.bytes[j] = src.bytes[ num_bytes-1 - j ];
        }
        
        // save our computed value
        (void)memcpy(&dst_data[i], &dst.word, num_bytes);
    }
    
    return true; 
}

