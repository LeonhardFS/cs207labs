

typedef struct DArray {
    int upto;
    int size;
    int *array;
} DArray;

int DArray_init(DArray* arr);
int append(DArray* arr, int i);
int get(DArray* arr, int index);
int get_index(DArray* arr, int value);
int set(DArray* arr, int index, int value);
int delete(DArray* arr, int value);
void DArray_free(DArray* arr);