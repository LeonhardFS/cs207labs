#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define N_HASHES 3

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
typedef uint64_t index_t;

// this type is already defined in sys/types
//typedef uint64_t key_t;
#define key_t uint64_t

typedef struct {
  index_t size; // in bits
  index_t count; // in bits
  index_t *table;
} bloom_filter_t;

void set_bit(bloom_filter_t *B, index_t i);
index_t get_bit(bloom_filter_t *B, index_t i);

index_t hash1(bloom_filter_t *B, key_t k);
index_t hash2(bloom_filter_t *B, key_t k);

void bloom_init(bloom_filter_t *B, index_t size_in_bits);
void bloom_destroy(bloom_filter_t *B);

int  bloom_check(bloom_filter_t *B, key_t k);
void bloom_add(bloom_filter_t *B, key_t k);