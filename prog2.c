#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


void printChunks(char **chunks, int *bytes_left, int N, int size){
    int bytes_used = 0;
    for(int i = 0; i< N; i++){

        bytes_used = size - bytes_left[i];

        printf("%6d: ", bytes_used);
        
        for(int j = 0; j < bytes_used-1; j++){
            if(chunks[i][j] == 0){
                printf(" ");
            }else{
                printf("%c", chunks[i][j]);
            }
        }
        printf("\n");
    }
}
  
void freeMem(char **arr, int n){
    for(int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr);
    arr = NULL;
}

  
void processInput(FILE *fp, int chunk_size){
    int count = 10; // initial size of bucket is 10, and chunks 0
    int current_chunk = 0; 
    //int current_chunk_size = 0;
    char line[100]; // temporary array to read a word
    int word_size = 0;
    int* bytes_left = (int *)malloc(count*sizeof(int));
    char** str_arr = (char **)malloc(count*sizeof(char *)); // creates 10 pointers, 
    char* temp = NULL;                                                  // that can later point to chunks
    int total_chunks = 0;

    // reads the input words and puts them in chunks
    while(fscanf(fp, " %s", line) != EOF){
        //printf("%s\n", line);
        word_size = strlen(line)+1;
        
        if(total_chunks == count){
            count += 10;
            char** new_arr = (char **)realloc(str_arr, count*sizeof(char *));
            if(new_arr == NULL){
                printf("Memory Error!");
                break;
            }else{
                str_arr = new_arr;
            }

            int* int_arr = (int *)realloc(bytes_left, count*sizeof(int));
            if(int_arr == NULL){
                printf("Memory Error!");
                break;
            }else{
                bytes_left = int_arr;
            }
        }

        // finds a suitable chunk and puts the word
        for(current_chunk = 0; current_chunk < count; current_chunk++){
            if(current_chunk == total_chunks){
                str_arr[current_chunk] = (char *)malloc(chunk_size);
                total_chunks++;
                bytes_left[current_chunk] = chunk_size;
            }
            temp = str_arr[current_chunk];
            if(word_size <= bytes_left[current_chunk]){
                temp += chunk_size-bytes_left[current_chunk];
                strcpy(temp, line);
                bytes_left[current_chunk] -= word_size;
                break; 
            }   

        } // end of for  

    } // end of while (read job)

    // print the chunks
    printChunks(str_arr, bytes_left, total_chunks, chunk_size);
    // frees up all dynamically allocated memory 
    // bytes_left, str_arr[][]
    freeMem(str_arr, total_chunks);
    free(bytes_left);
    //return str_arr;
}

int main(int argc, char** argv){
    int x = 100;
    char *filename = NULL;
    FILE *fp = NULL;
    if(argc > 1){
        x = atoi(argv[1]);
    }
    if(x<20 || x>100000){
        fprintf(stderr, "%d is not a valid input, must be in range (20-1,00,000).\n", x);
        return 1;
    }
    //printf("%d\n", argc);
    if(argc > 2){
        filename = argv[2];
        fp = fopen(filename, "r");
        if(fp == NULL){
            printf("\n ****ERROR: Cannot open the file! 3rd argument is optinal, if provided it must be a file.\n");
            return 1;
        }
        //printf("File Mode\n");
        processInput(fp, x);
        fclose(fp);
    }else{
        //printf("user mode");
        processInput(stdin, x);
    }

    //printf("%d\n", x);
    return 0;
}