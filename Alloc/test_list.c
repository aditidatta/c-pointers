#include <stdio.h>
#include <stdlib.h>
#include "List.h"


int main(int args, char** argv)
{
    
    void *mem = malloc(10);
    struct Node* list = NULL;
    void *temp = mem;
    int n = 0;
    while(n < 10){
        if(list == NULL){
            list = constructList(temp,1);
        }else{
            insert(list, temp,1);
        }
        temp++;
        n++;
    }

    removeItem(list, mem+3);
    removeItem(list, mem+7);

    printf("\n%ld\n", size(list));
    void** l = traverse(list);
    printf("\n%ld\n", list->ptr-mem);
    /*
    for(int i = 0; i < size; i++){
        printf("%p, ", l[i]);
    }
    printf("\n");
    */
    //struct Node* tr = list;
    
    //char* str = traverse2(list);


    //fprintf(stdout, "List: %s.\n", str);
    //free(str);
    free(l);
    destroyList(list);

    free(mem);
    list = NULL;
    
    mem = NULL;
    temp = NULL;
    
    return 0;

}