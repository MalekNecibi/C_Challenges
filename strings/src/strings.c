#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/strings.h"

#define UNUSED(x) (void)(x)


// Tested functions are intentially NOT reused to simplify evaluation via unit tests


// Bounded strlen custom implementation
// Matches specification of strnlen_s
size_t _strnlen(const char *str, size_t strsz) {
    
    // Justification for use of memchr()
    // strlen : allows buffer overflow
    // strnlen : POSIX-specific (_POSIX_C_SOURCE >= 200809L)
    // strnlen_s : Windows-only in practice

    // basic parameter checking
    if ( !str || 0 == strsz) {
        return 0;
    }
    
    const char* str_terminator = memchr(str, '\0', strsz);
    if ( !str_terminator ) {
        // string is at longer than provided size
        return strsz;
    }
    
    return (str_terminator - str);
}


// `length` includes the null terminator
bool string_valid(const char *str, const size_t length)
{
    if ( !str || 0 == length ) {
        return false;
    }
    
    return length == 1 + _strnlen(str, length);
}

char *string_duplicate(const char *str, const size_t length)
{
    if ( !str || 0 == length) {
        return false;
    }

    // allocate space for string + terminator
    char* new_string = malloc( (1 + length) * sizeof(char) );
    if ( !new_string ) {
        return NULL;
    }

    // copy substring
    strncpy(new_string, str, length);
    
    // append terminator (strncpy might not)
    new_string[length] = '\0';
    
    return new_string;
}

bool string_equal(const char *str_a, const char *str_b, const size_t length)
{
    if (!str_a || !str_b || 0 == length) {
        return false;
    }
    
    int compare = strncmp(str_a, str_b, length);
    
    return 0 == compare;
}

int string_length(const char *str, const size_t length)
{
    if ( !str || 0 == length ) {
        return -1;
    }
    
    return _strnlen(str, length);
}

int string_tokenize(const char *str, const char *delims, const size_t str_length, char **tokens, const size_t max_token_length, const size_t requested_tokens)
{
    
    // basic param check
    if ( !str || !delims || 0 == str_length || !tokens || 0 == max_token_length || 0 == requested_tokens) {
        return 0;
    }
    
    // ensure return array can be filled
    for (size_t i = 0; i < requested_tokens; i++) {
        // need space for the identified tokens to be inserted
        if ( !tokens[i] ) {
            return -1;
        }
    }

    // create mutable clone for tokenizer
    char* tmp_str = malloc( (1+str_length) * sizeof(char) );
    strncpy(tmp_str, str, str_length);
    tmp_str[str_length] = '\0';

    char* token = strtok(tmp_str, delims);
    size_t token_count = 0;
    while (token && token_count < requested_tokens) {
        strncpy(tokens[token_count], token, max_token_length);

        token = strtok(NULL, delims);
        token_count++;
    }
    
    free(tmp_str);
    return token_count;
}

bool string_to_int(const char *str, int *converted_value)
{
    //UNUSED(str); UNUSED(converted_value);
    
    if ( !str || !converted_value ) {
        return false;
    }
    
    char* new_str = NULL;
    long value = strtol(str, &new_str, 10);
    
    if ( (int)value == value ) {
        // doesn't overflow!
        *converted_value = (int)value;
        return true;
    }
    
    return false;
}
