#include "../include/allocation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const size_t FILENAME_MAX_LENGTH = 64;
const char*  FILENAME_ILLEGAL_CHARS = "#%&{}<>*?/$!':@\"\\\r\n\t";

// custom helper function : same one used in system_programming
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


void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
    // basic parameter checking
    if (0 == member_size || 0 == nmember) {
        return NULL;
    }
    
    // only use clear-allocate if clear-bit set 
    if (clear) {
        return calloc(nmember, member_size);
    }
    
    return malloc(nmember * member_size);
}

void* reallocate_array(void* ptr, size_t size)
{
    // basic parameter checking
    if (!ptr || 0 == size) {
        return NULL;
    }

    return realloc(ptr, size);
}

void deallocate_array(void** ptr)
{
    // basic parameter checking
    if (!ptr) {
        return;
    }
    
    // free the desired memory
    free(*ptr);
    // prevent that memory location from accidentally being used again
    *ptr = NULL;
}

char* read_line_to_buffer(char* filename)
{
    // basic parameter checking
    if (!legal_filename(filename)) {
        return NULL;
    }
    
    // open desired file
    FILE* fp = fopen(filename, "r");    // could open as binary "rb" but not necessary 
    if (!fp) {
        return NULL;
    }

    char* buffer = NULL;
    
    // TODO: repetitive close and abort

    // Get file size in bytes:
    // advance to end of file
    if (0 != fseek(fp, 0, SEEK_END)) {
        fclose(fp);
        return NULL;
    }
    
    // count number of bytes elapsed
    size_t file_size = ftell(fp);
    
    // rewind to start of file
    rewind(fp);
    
    // allocate buffer
    buffer = malloc(file_size * sizeof(char));
    if (!buffer) {
        fclose(fp);
        return NULL;
    }
    
    fread(buffer, sizeof(char), file_size, fp);
    
    fclose(fp);
    return buffer;
}

