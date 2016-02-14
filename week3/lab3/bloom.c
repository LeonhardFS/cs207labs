#include "bloom.h"

const char *byte_to_binary(index_t x)
{
    static char b[128];
    b[0] = '\0';
    
    index_t z;
    for (z = (0x1UL << 32); z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    
    return b;
}

void set_bit(bloom_filter_t *B, index_t i) {
    index_t wsize = (sizeof(index_t) * 8);
	index_t bit_position = i % wsize; // % 64
	index_t bit_index = i / wsize; // / 64

	// check that valid index was submitted
	assert(i < B->size);
    B->table[bit_index] |= (0x1UL << bit_position);
}

index_t get_bit(bloom_filter_t *B, index_t i) {
	assert(i < B->size);
    index_t wsize = (sizeof(index_t) * 8);
    index_t test =(B->table[i / wsize] >> (i % wsize));
    return (B->table[i / wsize] >> (i % wsize)) & 0x1;
}

index_t hash1(bloom_filter_t *B, key_t k) {
	// using FNV1-hash
	//https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
	
	key_t hash = 0xcbf29ce484222325;
	key_t fnv_prime = 0x100000001b3;

	key_t mask = 0xff;
	int pos = 0;
	while(mask) {
		hash = hash * fnv_prime;
		hash = hash ^ ((k & mask) >> pos);

		// shift mask by 8
		pos += 8;
		mask <<= 8;
	}

	return hash;
}

index_t hash2(bloom_filter_t *B, key_t k) {
	// after http://stackoverflow.com/questions/5085915/what-is-the-best-hash-function-for-uint64-t-keys-ranging-from-0-to-its-max-value
	// Numerical Recipes, part 3

	index_t v = k * 3935559000370003845 + 2691343689449507681;

	v ^= v >> 21;
	v ^= v << 37;
	v ^= v >>  4;

	v *= 4768777513237032717;

	v ^= v << 20;
	v ^= v >> 41;
	v ^= v <<  5;

  return v;
}

index_t bit2index_t_size(index_t bit_size) {
	index_t size = bit_size / (sizeof(index_t) * 8);
	
	// we need one more byte to store information
	if(bit_size % (sizeof(index_t) * 8) != 0)size++;

	return size;
}

void bloom_init(bloom_filter_t *B, index_t size_in_bits) {
	// free old space
	if(B->table)free(B->table);

	B->size = size_in_bits;
	B->count = 0;
	B->table = (index_t*)malloc(sizeof(index_t) * bit2index_t_size(B->size));
	if(!B->table) {
		printf("memory error\n");
		return;
	}
	// set values to zero
	memset(B->table, 0, sizeof(index_t) * bit2index_t_size(B->size));
}

void bloom_destroy(bloom_filter_t *B){
	if(B) {
		if(B->table)free(B->table);
		B->table = NULL;
		free(B);
	}
}

int  bloom_check(bloom_filter_t *B, key_t k) {
    // hash N_HASHES times
    for(index_t i = 0; i < N_HASHES; i++) {
        index_t hash = (hash1(NULL, k) + i * hash2(NULL, k)) % B->size;
        
       // if the bit is not set, the key is not stored
        if(!get_bit(B, hash))return FALSE;
    }
    
    // note that this might lead to a false positive
    return TRUE;
}
void bloom_add(bloom_filter_t *B, key_t k) {
    // hash N_HASHES times
    for(index_t i = 0; i < N_HASHES; i++) {
        index_t hash = (hash1(NULL, k) + i * hash2(NULL, k)) % B->size;
        
        // check if bit is already set
        if(!get_bit(B, hash)) {
            set_bit(B, hash);
            B->count++;
        }
    }
}

index_t bloom_count_bits(bloom_filter_t *B) {
    assert(B);
    
    index_t count = 0;
    for(index_t i = 0; i < B->size; i++) {
        if(get_bit(B, i))count++;
    }
    return count;
}

int main() {

    bloom_filter_t *bloom = (bloom_filter_t*)malloc(sizeof(bloom_filter_t));
    bloom->table = NULL;


	int test_keys[] = {0, 1, 2, 3, 13, 97};
	for(int i = 0; i < 6; i++) {
		printf("key %2d: %2d  hash1: %llu\thash2: %llu\n",
		 i+1, test_keys[i], hash1(NULL, test_keys[i]),
		  hash2(NULL, test_keys[i]));
	}

    // Bloom filter test:
    // ---
    // init empty bloom (this is actually a really bad way to do it)
    bloom_init(bloom, 1000);
    
    // add first 70 positive integers
    for(key_t i = 1UL; i <= 71UL; i++) {
        bloom_add(bloom, i);
    }
    
    // number of bits set in filter
    printf("first 70 positive integers results:\n");
    printf("number of bits set %llu / %llu\n", bloom->count, bloom->size);
    // calling the requested function  (this is completely unnecssary)
    //printf("number of bits set %llu / %llu\n", bloom_count_bits(bloom), bloom->size);
    
    // second part:
    // clear filter
	memset(bloom->table, 0, sizeof(index_t) * bit2index_t_size(bloom->size));
    printf("RAND_MAX is %d\n", RAND_MAX);
    
    // In this implementation, there is no array creation done
    // as it is unnecessary. All operations can be performed directly
    int num_rand_numbers = 100;
    for(int i = 0; i < num_rand_numbers; i++) {
        // random numbers from 0...1000000 (excluding)
        key_t rand_number = (key_t)rand() % 1000000;
        bloom_add(bloom, rand_number);
    }
    
    // now generate more random numbers and check if they are in the filter
    int num_contained = 0;
    for(int i = 0; i < num_rand_numbers; i++) {
        // random numbers from 0...1000000 (excluding)
        key_t rand_number = (key_t)rand() % 1000000;
        if(bloom_check(bloom, rand_number))num_contained++;
    }
    // print results
    printf("occupancy: %d bits  false positives: %d\n", (int)bloom->count, num_contained);
    
    // inser 100 random numbers between 0 and 1000000
    for(key_t i = 1UL; i <= 71UL; i++) {
        bloom_add(bloom, rand() % 1000000);
    }
    
	bloom_destroy(bloom);
	return 0;
}