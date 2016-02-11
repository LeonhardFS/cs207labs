
#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int value;
    struct item* rest;
} Item;

Item* new_item(int value){
    Item* newitem = (Item *) malloc(sizeof(Item));
    newitem->value = value;
    newitem->rest = NULL;
    return newitem;
}

Item* insert_front(Item* listptr, int value){
    Item* newitem = new_item(value);
    newitem->rest = listptr;
    return newitem;
}

int get_index(Item *listptr, int value) {
    
    // empty list?
    if(!listptr)return -1;
    
    Item *cur = listptr;
    int index = 0;
    while(cur) {
        if(cur->value == value)break;
        index++;
        cur = cur->rest;
    }
    
    // end of list reached?
    if(!cur)return -1;
    return index;
}

Item *remove_item(Item *listptr, int value) {
    if(!listptr)return NULL;
    
    Item *head = listptr;
    Item *cur = listptr;
    Item *prev = NULL;
    while(cur) {
        
        // Item found?
        if(cur->value == value) {
            // 2 cases
            if(!prev) {
                head = listptr->rest;
                free(listptr);
                return head;
            } else {
                prev->rest = cur->rest;
                free(cur);
                return head;
            }
        }
        
        prev = cur;
        cur = cur->rest;
    }
    
    return head;
}

int get(Item* listptr, int index){
    int ctr = 0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (ctr==index){
            return p->value;
        }
        ctr++;
    }
    return -1;
}


void free_all(Item* listptr) {
    Item *p;
    Item *next;
    for(p = listptr; p!= NULL; p = next){
        next = p->rest;
        free(p);
    }
}

/* for FUN part here */
Item* insert_back(Item *head, int value) {
    Item *new_entry = new_item(value);
    if(!new_entry)return NULL; // memory error
    
    // special case, empty head
    if(!head)return new_entry;
    
    // go through list till end
    Item *cur = head;
    Item *prev = NULL;
    while(cur) {
        prev = cur;
        cur = cur->rest;
    }
    prev->rest = new_entry;
    return head;
}

void set(Item* listptr, int index, int value){
    int ctr = 0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (ctr==index){
            p->value = value;
            break;
        }
        ctr++;
    }
}

int main(){
    Item* listptr;
    int i;
    listptr = new_item(0);
    for (i=1; i < 6; i++){
        listptr=insert_front(listptr, i);
    }
    for (i=0; i < 6; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    listptr = remove_item(listptr, 3);
    for (i=0; i <= 5; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    printf("Index for 3 %d\n", get_index(listptr, 3));
    
    /* fun part */
    insert_back(listptr, 42);
    printf("%dth Item has value %d\n", 4, get(listptr, 4));
    printf("What is the answer to life, the universe and everything?\n");
    set(listptr, 4, 42);
    printf("Now, it seems as if Deep Mind has responded, %dth Item has value %d\n", 4, get(listptr, 4));
    free_all(listptr);
}