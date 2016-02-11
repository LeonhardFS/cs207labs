
#include <stdio.h>
#include "dynamic_array.h"

int main() {
    DArray dynarray;
    DArray_init(&dynarray);
    printf("%d %d\n", dynarray.upto, dynarray.size);
    int i;
    for (i = 0; i < 200; i++) {
        append(&dynarray, i);
        printf("upto %d size %d val %d\n", dynarray.upto, dynarray.size, get(&dynarray, i));
    }
    for (i = 185; i < 190; i++) {
        set(&dynarray, i, i+1);
        printf("i %d val %d\n", i, get(&dynarray, i));
    }
    for (i = 180; i < 182; i++) {
        delete(&dynarray, i);
        printf("i %d val %d upto %d\n", i, get(&dynarray, i), dynarray.upto);
    }
    for (i = 180; i < 195; i++) {
        printf("val %d index %d\n", i, get_index(&dynarray, i));
    }
    DArray_free(&dynarray);
}