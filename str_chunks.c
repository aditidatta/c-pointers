#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void freeMem(char **arr, int n){
    for(int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr);
    arr = NULL;
}

int main(){
    int count = 10;
    char** str_arr = (char **)malloc(count*sizeof(char *));
    count = count + 10;
    char** new_arr = (char **)realloc(str_arr, count*sizeof(char *));
    if(new_arr == NULL){
        printf("Memory Error!");
    }else{
        str_arr = new_arr;
    }
    for(int i = 0; i < count; i++){
        if(str_arr[i] == NULL){
            printf("It's NULL\n");
        }
    }
    printf("Done\n");
    freeMem(str_arr, 0);
    return 0;
}