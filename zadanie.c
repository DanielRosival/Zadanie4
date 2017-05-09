#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct OWN{
    int data;
    struct OWN *next;
} OWN;

typedef struct {
    OWN *beg;
    OWN *cur;
} LOWL;

LOWL *lowl_create_empty(void){
    LOWL *pointer = (LOWL*) malloc(sizeof(LOWL));
    if ( pointer == NULL)
    {
        printf("Creation failed!\n");
        return NULL;
    }
    pointer -> beg = NULL;
    pointer -> cur = NULL;
    
    return pointer;
}

LOWL *lowl_create_random(unsigned int size){
    LOWL *pointer = (LOWL*) malloc(sizeof(LOWL));
    
    if ( pointer == NULL )
    {
        printf("Creation failed\n");
        return NULL;
    }
    
    
    pointer -> beg = (OWN*) malloc (sizeof(OWN));
    pointer -> cur = (OWN*) malloc(sizeof(OWN)*size);
    
    if (pointer -> beg == NULL)
    {
        printf("Creation failed!\n");
        return NULL;
    }
    
    if (pointer -> cur == NULL)
    {
        printf("Creation failed!\n");
        return NULL;
    }
    
    pointer -> beg -> data = 999;
    pointer -> beg -> next = pointer -> cur;
    
    for (int i = 0; i < size; i++ )
    {
        ((pointer -> cur)+i) -> data = rand()%100 + 1;
        if (i < size - 1)
        {
            ((pointer -> cur)+i) -> next = ((pointer -> cur)+ i + 1);
        }
        else
        {
            ((pointer -> cur)+i) -> next = NULL;
        }
    }
    
    
    return pointer;
}


void lowl_destroy(LOWL *list){
    list -> cur = list -> beg;
     struct OWN* next;
    
    while ( (list -> cur) != NULL )
    {
        next = list -> cur -> next;
        free(list -> cur);
        list -> cur = next;
    }
    
    list -> beg = NULL;
    list -> cur = NULL;
};



int main(int argc, char const *argv[])
{
    srand(time(NULL));
    return 0;
}