#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"List.h"

int main(int argc, char **argv)
{
    struct Node *myList = constructList(0);

    if(argc != 3)
    {
        fprintf(stderr, "Not enough arguments: %s <count> <seed>\n", argv[0]);
        return 1;
    }
    int count = atoi(argv[1]);
    int seed = atoi(argv[2]);

    srand(seed);

    char commands[8] = "csifr";
    for(int i=0; i<count; i++)
    {
        char rCommand = commands[rand() % 5];
        int rOption = rand() % 64;

        char command = ' ';
        char rBuffer[100];
        sprintf(rBuffer, "-%c:%d", rCommand, rOption);
        int option = 0;
        fprintf(stderr, "Processing command '%s'.\n", rBuffer);
        sscanf(rBuffer, "-%c:%d", &command, &option);
        //printf("\n%c\n", command);
        switch(command)
	    {
	        case 'c':
	            myList = destroyList(myList);
	            myList = constructList(option);
	            break;
	        case 's':
	            size(myList);
	            break;
	        case 'i':
	            myList = insert(myList, option);
	            break;
	        case 'f':
	            find(myList, option);
	            break;
	        case 'r':
	            myList = removeItem(myList, option);
	            break;
	    }

        //printf("next buffer\n");
      //Dangerous estimate
        char *buffer = (char *)calloc(1, 250000 * sizeof(char));
        if(traverse(myList, buffer) == 0)
	    {
	        fprintf(stdout, "List is empty.\n");
	    }
        else
	    {
	        fprintf(stdout, "List: %s.\n", buffer);
	    }
        free(buffer);

        char *printable = traverse2(myList);
        fprintf(stdout, "List: %s.\n", printable);
        free(printable);
    }

  //Dangerous estimate
    char *buffer = (char *)calloc(1, 250000 * sizeof(char));
    traverse(myList, buffer);
    fprintf(stdout, "%s\n", buffer);
    free(buffer);

    char *printable = traverse2(myList);
    fprintf(stdout, "%s\n", printable);
    free(printable);

    myList = destroyList(myList);
  //valgrind should report no memory leaks at this point

    return 0;
}
