#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWL_SUCCESS 1
#define BOUNDARY_REACHED -1
#define LOWL_OK 1
#define LOWL_PROBLEM -1
#define LOWL_FAIL -1

typedef struct OWN{
    int data;
    struct OWN *next;
} OWN;

typedef struct {
    OWN *beg;
    OWN *cur;
} LOWL;


OWN *find_prev(LOWL *list){

    OWN *prev,*temp;
    prev = list->beg;
    temp = list->beg->next;

    if (list ==  NULL || list->beg == NULL){
        return 1;

    }
    else if(list->beg->next == NULL){
        return 2;

    }
    else{
        while(temp != NULL){
            if(temp == list->cur){
                return prev;
            }
            else{
                temp = temp->next;
                prev = prev->next;
            }

        }


    }


}

LOWL *lowl_create_empty(void){
    LOWL *temp;

    temp = malloc(sizeof(LOWL));

    if ( temp == NULL)
    {
        printf("Creation failed!\n");
        return NULL;
    }

    temp -> beg = NULL;
    temp -> cur = NULL;

    return temp;
}

LOWL *lowl_create_random(unsigned int size){
    LOWL *temp;

    temp = lowl_create_empty();

    if ( temp == NULL )
    {
        printf("Creation failed\n");
        return NULL;
    }


    temp -> beg = (OWN*) malloc (sizeof(OWN));
    temp -> cur = (OWN*) malloc (sizeof(OWN));

    if (temp -> beg == NULL)
    {
        printf("Creation failed!\n");
        return NULL;
    }

    if (temp -> cur == NULL)
    {
        printf("Creation failed!\n");
        return NULL;
    }

    temp -> beg -> data = rand()%100 + 1;
    temp -> beg -> next = temp -> cur;

    for (int i = 0; i < size - 1; i++ )
    {
        ((temp -> cur)+i) -> data = rand()%100 + 1;
        if (i < size - 2)
        {
            ((temp -> cur)+i) -> next = ((temp -> cur) + i + 1);
        }
        else
        {
            ((temp -> cur)+i) -> next = NULL;
        }
    }

    return temp;
}


void lowl_print(LOWL *list) {
    OWN *temp;

    temp = list -> beg;

    while (temp != NULL){
        printf("%d\n", temp -> data);
        temp = temp -> next;
    }
}

char lowl_cur_step_right(LOWL *list) {

    if (list -> cur -> next == NULL) {
        return BOUNDARY_REACHED;
    }
    else {
        list -> cur = list -> cur -> next;
    }

    return LOWL_SUCCESS;
}

char lowl_cur_step_left(LOWL *list) {
    OWN *prev;

    prev = find_prev(list);

    if ( prev == 2 || prev == 1) {
        return BOUNDARY_REACHED;
    }
    else {
        list -> cur = prev;
    }

    return LOWL_SUCCESS;
}

OWN *lowl_insert_right(LOWL* list, int val) {
    OWN *node = malloc(sizeof(OWN));
    node->data = val;
    node->next = NULL;
    if(list->beg == NULL){
        list->beg = node;
        list->cur = node;
        return node;
    }
    else if(list->cur->next == NULL){
        list->cur->next = node;
        list->cur = node;
        return node;
    }
    else{
        node->next = list->cur->next;
        list->cur->next = node;
        list->cur = node;
        return node;
    }
}

OWN *lowl_insert_left(LOWL* list, int val) {
    OWN *node = malloc(sizeof(OWN));
    OWN *prev = find_prev(list);
    node->data = val;
    node->next = NULL;
    if(list->beg == NULL){
        list->beg = node;
        list->cur = node;
        return node;
    }
    else if(list->cur == list->beg){
        node->next = list->beg;
        list->beg = node;
        list->cur = node;
        return node;
    }
    else{
        node->next = prev->next;
        prev->next = node;
        list->cur = node;
        return node;
    }
}


void create_svg (FILE *f, int max_value, int h) {
    fprintf(f, "<html>\n");
    fprintf(f, "<body>\n");
}

void finish_svg ( FILE *f) {
    fprintf(f, "</body>\n");
    fprintf(f, "</html>\n");
}


char lowl_visualize_schema_svg(LOWL *list, char *filename) {
    FILE *f;
    OWN *temp;
    int counter = 0, max_value, i = 1;

    temp = list -> beg;
    max_value = temp -> data;

    while (temp != NULL){
        counter++;
        if ( max_value < temp -> data) {
            max_value= temp -> data;
        }
        temp = temp -> next;
    }

    f = fopen (filename, "w");

    if (f == NULL ) {
        return LOWL_PROBLEM;
    }

    create_svg (f, max_value*10, counter*10);

    temp = list -> beg;


    while (temp != NULL){
        fprintf(f, "%d.\n", i);
        fprintf(f, "<svg width=\"%d\" height=\"%d\"> \n", max_value*10, 20);
        fprintf(f, "<rect width=\"%d\" height=\"%d\" style=\"fill:rgb(%d,%d,%d);\" / > \n",  temp -> data*10, 20, rand()%255, rand()%255, rand()%255);
        fprintf(f, "</svg>\n");
        fprintf(f, "%d\n", temp -> data);
        fprintf(f, "<br>\n");
        fprintf(f, "<br>\n");
        temp = temp -> next;
        i++;
    }

    finish_svg(f);

    fclose(f);

    return LOWL_OK;

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
}

char lowl_delete(LOWL *list) {
    OWN  *prev;
    prev = find_prev(list);
    if (prev == 2){
        lowl_destroy(list);
        return LOWL_OK;
    }
    else if(prev == 1){
        return LOWL_OK;
    }
    else{
        if(list->cur->next == NULL){
            prev->next = NULL;
            list->cur = prev;
            return LOWL_OK;
        }
        else{
            prev->next = list->cur->next;
            list->cur = list->cur->next;
            return LOWL_OK;
        }
    }

    return LOWL_FAIL;
}


int main(int argc, char const *argv[])
{
    LOWL *temp;

    srand(time(NULL));

    temp = lowl_create_random(50);
    lowl_print(temp);

    lowl_visualize_schema_svg( temp, "visualize.html");

    return 0;
}
