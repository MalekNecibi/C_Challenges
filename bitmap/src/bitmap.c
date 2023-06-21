#include <stdio.h>
#include "../include/bitmap.h"

// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create


bitmap_t *bitmap_create(size_t n_bits)
{
    // basic parameter validation
    if (0 == n_bits) {
        return NULL;
    }

    // equivalent to ceil( n_bits / 8 ), except rare overflow
    size_t n_bytes = (n_bits + 7) / 8;
    
    // first allocate larger data, more likely to fail than bitmap_t container
    

    uint8_t* data = calloc(n_bytes, sizeof(uint8_t) );
    if (!data) {
        return NULL;
    }

    bitmap_t* map = calloc(1, sizeof(bitmap_t));
    if (!map) {
        // TODO : centralized free management?
        free(data);
        return NULL;
    }
    
    map->data = data;
    map->bit_count = n_bits;
    map->byte_count = n_bytes;
    
    return map;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit)
{
	if (!bitmap
    || !bitmap->data
    || bit >= bitmap->bit_count) {
        return false;
    }

    // treat like a 2d array [byte][bit]
    size_t byte_num = bit / 8;
    size_t bit_offset = bit % 8;
    
    // force target bit high by logical OR with 1 on target bit
    uint8_t bit_mask = (0b1 << bit_offset);
    bitmap->data[byte_num] |= bit_mask;
    
    // confirm the change actually worked
    return (bitmap->data[byte_num] & bit_mask) != 0;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit)
{
	if (!bitmap
    || !bitmap->data
    || bit >= bitmap->bit_count) {
        return false;
    }
    
    // TODO: DRY principle violation (bitmap_set)

    // treat like a 2d array [byte][bit]
    size_t byte_num = bit / 8;
    size_t bit_offset = bit % 8;
    
    // force target bit low by logical AND with 0 on target bit
    // NOTE: remember bitwise inversion
    uint8_t bit_mask = ~(0b1 << bit_offset);
    bitmap->data[byte_num] &= bit_mask;
    
    // confirm the change actually worked
    // 0b11111011 | NUM == 0b11111011 iff mask bit is low
    return (bitmap->data[byte_num] | bit_mask) == bit_mask;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit)
{
	if (!bitmap
    || !bitmap->data
    || bit >= bitmap->bit_count) {
        return false;
    }
    
    // TODO: DRY principle violations

    // treat like a 2d array [byte][bit]
    size_t byte_num = bit / 8;
    size_t bit_offset = bit % 8;

    // shift target bit to 1's-place
    // force all non-1's-place bits low
    return (bitmap->data[byte_num] >> bit_offset) && 0b1;
}

size_t bitmap_ffs(const bitmap_t *const bitmap)
{
	if (!bitmap
    || !bitmap->data) {
        return SIZE_MAX;
    }
    
    size_t result = SIZE_MAX;

    for (size_t i = 0; i < bitmap->byte_count; i++) {
        
        uint8_t byte = bitmap->data[i];
        if (byte != 0) {
            // found the first set byte!
            for (int j = 0; j < 8; j++) {
                // check each bit systematically, comparing againt mask of 1
                if ( 1 == (0b1 & (byte >> j)) ) {
                    // exact bit found!
                    result = i * 8 + j;
                    break;
                }
            }
        }
        // once found, break doesn't escape both for loops
        if (result != SIZE_MAX) {
            break;
        }
    }   
    
    // ignore if overflow bit_count
    if (result >= bitmap->bit_count) {
        result = SIZE_MAX;
    }

    return result;
}

size_t bitmap_ffz(const bitmap_t *const bitmap)
{
    if (!bitmap
    || !bitmap->data) {
        return SIZE_MAX;
    }
    
    // TODO: DRY principle violation

    size_t result = SIZE_MAX;
    
    for (size_t i = 0; i < bitmap->byte_count; i++) {
        uint8_t byte = bitmap->data[i];
        if (byte < 0xFF) {
            // found the first zero bit!
            for (int j = 0; j < 8; j++) {
                // check each bit systematically, comparing againt mask of 1
                if (0 == (0b1 & (byte >> j))) {
                    // exact bit found!
                    result = i * 8 + j;
                    break;
                }
            }
        }
        // once found, break doesn't escape both for loops
        if (result != SIZE_MAX) {
            break;
        }
    }

    // ignore if overflow bit_count
    if (result >= bitmap->bit_count) {
        result = SIZE_MAX;
    }
    
    return result;
}

bool bitmap_destroy(bitmap_t *bitmap)
{
    if (!bitmap) {
        return false;
    }
    if ( bitmap->data ) {
        free(bitmap->data);
    }
    return true;
}
