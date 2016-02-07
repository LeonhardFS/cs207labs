
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

int CAPACITY_INIT = 1;
int GROWTH_FACTOR = 2;

int DArray_init(DArray* arr){
    arr->array = (int *) malloc(CAPACITY_INIT*sizeof(int));
    if (arr->array == NULL) {
        return -1;
    }
    arr->upto = 0;
    arr->size = CAPACITY_INIT;
    return 1;
}

int append(DArray* arr, int i){
    int *iptr;
    if (arr->upto >= arr->size) {
        /* tmp pointer needed below as if allocation failed, original array would be lost */
        iptr = (int *) realloc(arr->array, arr->size*GROWTH_FACTOR*sizeof(int));
        if (iptr == NULL) {
            return -1;
        }
        arr->array = iptr;
        arr->size *= GROWTH_FACTOR;
    }
    arr->array[arr->upto] = i;
    return arr->upto++;
    
        
}

int get(DArray* arr, int index) {
    if (index >= arr->upto || index < 0) {
        return -1;
    }
    return arr->array[index];
}

int set(DArray* arr, int index, int value) {
    /* update array value at index */
    if (index >= arr->upto || index < 0) {
        return -1;
    }
    arr->array[index] = value;
    return arr->array[index];
    
}

int delete(DArray* arr, int value) {
    int index = 0;
    while(arr->array[index] != value && index < arr->upto)index++;
    
    /* value not found? */
    if(index == arr->upto)return -1;
    
    arr->array[index] = arr->array[arr->upto - 1];
    arr->upto--;
    
    /* adjust size if necessary */
    int *iptr;
    if (arr->upto < arr->size / GROWTH_FACTOR) {
        /* tmp pointer needed below as if allocation failed, original array would be lost */
        iptr = (int *) realloc(arr->array, arr->size*GROWTH_FACTOR*sizeof(int));
        if (iptr == NULL) {
            return -1;
        }
        arr->array = iptr;
        arr->size /= GROWTH_FACTOR;
    }
    
    /* everything ok, return 0 */
    return 0;
}

int get_index(DArray* arr, int value) {
    int i;
    for (i=0; i< arr->upto; i++){
        if (arr->array[i]==value) {
            return i;
        }
    }
    return -1;
}

void DArray_free(DArray *arr) {
  free(arr->array);
}

/*your code here*/