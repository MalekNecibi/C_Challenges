#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "../include/error_handling.h"

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

int create_blank_records(Record_t **records, const size_t num_records)
{
    // records holder should start out NULL
	if (!records || NULL != *records || 0 == num_records) {
        return -1;
    }
    
    *records = (Record_t*) malloc(sizeof(Record_t) * num_records);
    if (!*records) {
        return -2;
    }
    
	memset(*records,0,sizeof(Record_t) * num_records);
    return 0;	
}

int read_records(const char *input_filename, Record_t *records, const size_t num_records) {
    
    if (!legal_filename(input_filename) || !records || 0 == num_records) {
        return -1;
    }

	int fd = open(input_filename, O_RDONLY);
    if (fd < 0) {
        return -2;
    }
    
	ssize_t data_read = 0;
	for (size_t i = 0; i < num_records; ++i) {
		data_read = read(fd, &records[i], sizeof(Record_t));
        if (data_read <= 0) {
            // error: failed to continue reading
            // TODO: should read to temporary, then copy later
            close(fd);
            return -3;
        }
	}
    
    close(fd);
	return 0;
}

int create_record(Record_t **new_record, const char* name, int age)
{
    if (!new_record || NULL != *new_record || !legal_filename(name) || age < 1 || age > 200) {
        // invalid parameters
        return -1;
    }
    
    *new_record = (Record_t*) malloc(sizeof(Record_t));
	if (!*new_record) {
        // error: failed to allocate memory
        return -2;
    }
    
    // write provided data to new allocated record
	memcpy((*new_record)->name,name,sizeof(char) * strlen(name));
	(*new_record)->name[MAX_NAME_LEN - 1] = 0;	
	(*new_record)->age = age;

	return 0;
}
