#include <stdio.h>
#include <stdlib.h>


int main(int args, char** argv)
{
    
    char *mem = (char*)malloc(40);
    size_t sz = 16;
    //char* ptr = mem;
    char* temp = mem+16;
    
    fprintf(stderr, "%p\n", mem);
    fprintf(stderr, "%p\n", temp);

    free(mem);
    
    mem = NULL;
    temp = NULL;
    
    return 0;

}