#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void swapLines(char** str_arr, int n){
  char *temp = NULL;
  for(int i = 1; i < n; i+=2){
    temp = str_arr[i];
    str_arr[i] = str_arr[i-1];
    str_arr[i-1] = temp;
  }
}

void swapCase(char* str){
  char *begin = str;
  char *end = str + strlen(str);
  while(begin < end){
    if(islower(*begin)){
      *begin = toupper(*begin);
    }else if(isupper(*begin)){
      *begin = tolower(*begin);
    }
    begin++;
  }
}

void reverse(char* str, int n){
  char *begin = str;
  char *end = str + n-1;
  char temp;

  while(begin < end){
    temp = *begin;
    *begin = *end;
    *end = temp;
    begin++;
    end--;
  }
}

void reverseEachWord(char* str){
  int word_end = 0;
  char *begin = str;
  char *end = str + strlen(str);
  char* token = begin;

  while(begin < end){
    if(!isalpha(*begin) && word_end == 0 && token != begin){
      reverse(token, (begin-token));
      word_end = 1;
    }else if(isalpha(*begin) && word_end == 1){
      token = begin;
      word_end = 0;
    }
    else if(begin == end-1 && isalpha(*begin)){
        reverse(token, (begin-token));
        word_end = 1;
    }
    begin++;
  }

}

void printLines(char** str_arr, int n){
  for(int i= 0; i < n; i++){
    printf("%s\n",str_arr[i]);
  }
}

void ops(char** str_arr, int n, int r, int e, int s, int t){
  if(s == 1){
    swapLines(str_arr, n);
  }
  for(int i= 0; i < n; i++){
    if(r == 1){
      reverseEachWord(str_arr[i]);
    }
    if(e == 1){
      reverse(str_arr[i], strlen(str_arr[i]));
    }
    if(t == 1){
      swapCase(str_arr[i]);
    }
  }
  
  printLines(str_arr, n);
}

char** read(FILE* in, int* n){
  int count = 10;
  char line[100];
  char** str_arr = (char **)malloc(count*sizeof(char *));
  while(fscanf(in, " %[^\n]s", line) != EOF){
    //printf("%s\n", line);
    if(*n == count){
      count += 10;
      char** new_arr = (char **)realloc(str_arr, count*sizeof(char *));
      if(new_arr == NULL){
        printf("Memory Error!");
        break;
      }else{
          str_arr = new_arr;
      }
    }
    str_arr[*n] = (char *)malloc(strlen(line)+1);
    strcpy(str_arr[*n], line);
    (*n)++;
  }
  return str_arr;
}

void freeMem(char **arr, int n){
  for(int i = 0; i < n; i++){
      free(arr[i]);
  }
  free(arr);
  arr = NULL;
}

void processInput(FILE *fp, int r, int e, int s, int t){
  int line_count = 0;
  char** lines = read(fp, &line_count);
  ops(lines, line_count, r, e, s, t);
  freeMem(lines, line_count);
}

int main(int argc, char **argv) {
  int r = 0;
  int e = 0;
  int s = 0;
  int t = 0;
  int file = 0;
  char *filename;
  FILE *fp;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {
      r = 1;
    }
    else  if (strcmp(argv[i],"-e") == 0) {
      e = 1;
    }
    else  if (strcmp(argv[i],"-s") == 0) {
      s = 1;
    }
    else  if (strcmp(argv[i],"-t") == 0) {
      t = 1;
    }
    else if (argv[i][0]=='-'){
      fprintf(stderr, "Invalid command line option \n");
      return 1;
    }
    else{
      file = 1;
      filename = argv[i];
    }
  }

  if(file==1){
    fp = fopen(filename, "r");
    if(fp == NULL){
      printf("\n ****ERROR: Cannot open the file!\n");
      return 1;
    }
    //printf("File Mode\n");
    processInput(fp, r, e, s, t);
    fclose(fp);
  }else{
    //printf("User Mode\n");
    processInput(stdin, r, e, s, t);
  }

  return 0;
}