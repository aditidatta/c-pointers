#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "List.h"



struct Node* constructList(void *ptr, size_t size)
{
    struct Node* node = (struct Node *)malloc(sizeof(struct Node));
    node->ptr = ptr;
    node->size = size;
    node->next = NULL;
    return node;
}

struct Node* destroyList(struct Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->next != NULL)
    {
        node->next = destroyList(node->next);
    }
    free(node);
    node = NULL;
    return node;
}

size_t size(struct Node* node)
{
    int count = 0;
    struct Node* temp = node;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

struct Node* insert(struct Node *node, void *ptr, size_t size)
{
    struct Node* newNode = NULL;
    struct Node* temp = node;
    
    if(node == NULL)
    {
        newNode = constructList(ptr, size);
        return newNode;
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = constructList(ptr, size);
        temp = NULL;
        return node;
    }
}


struct Node* find(struct Node* node, void *ptr)
{
    struct Node* temp = node;
    int found = 0;
    while(temp!=NULL)
    {
        if(temp->ptr == ptr)
        {
            found = 1;
            break; 
        }
        temp = temp->next;
    }
    if(found==1)
    {
        return temp;
    }
    else
    {
        return NULL;
    }
}

struct Node* findBySize(struct Node* node, size_t size)
{
    struct Node* temp = node;
    int found = 0;
    
    while(temp!=NULL)
    {
        if(temp->size >= size)
        {
            found = 1;
            break; 
        }
        temp = temp->next;
    }
    if(found == 1)
    {
        return temp;
    }
    else
    {
        return NULL;
    }
}

/*
char* traverse2(struct Node *node)
{
    char *str = (char *) malloc(10*sizeof(char));
    struct Node* temp = node;
    //char* buffer = str;
    int len = 10;
    int currPos = 0;
    while(temp!=NULL)
    {
        if(str+currPos >= str+len){
            len*=2;
            char* new_arr = (char *)realloc(str, len*sizeof(char));
            if(new_arr == NULL){
                printf("Memory Error!");
            }else{
                str = new_arr;
            }
        }
        if(temp->next == NULL)
        {
            sprintf(str+currPos, "%p", temp->ptr);
        }
        else
        {
            sprintf(str+currPos, "%p,", temp->ptr);
        }
        temp = temp->next;
        currPos = strlen(str);
    }
    
    char* buffer = (char *)malloc(currPos+1);
    strcpy(buffer,str);
    free(str);
    return buffer;
}
*/

void** traverse(struct Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    size_t n = size(node);
    void** list = (void**) malloc(n*sizeof(void*));
    void** temp = list;
    while(node != NULL){
        *temp = node->ptr;
        temp++;
        //printf("%p, ", node->ptr);
        node = node->next;
    }
    temp = NULL;
    //printf("\n");
    return list;
}


int traverse2(struct Node *node, char *str)
{
    struct Node* temp = node;
    char* buffer = str;
    int count = 0;
    while(temp!=NULL)
    {
        count++;
        sprintf(buffer, "(%p : %ld) ", temp->ptr, temp->size);
        temp = temp->next;
        buffer = buffer + strlen(buffer);
        //printf("\n%s\n", str);
    }
    return count;
}

struct Node* removeItem(struct Node *node, void *ptr)
{
    struct Node* temp = NULL;
    struct Node* prev = NULL;
    if(node == NULL)
    {
        return node;
    }
       
    temp = node;
    while (temp != NULL && temp->ptr == ptr)
    {
        //fprintf(stderr, "Removing 1..\n");
        node = temp->next;   
        free(temp);           
        temp = node;
    }
    
       
    while (temp != NULL)
    {
        while (temp != NULL && temp->ptr != ptr)
        {
            prev = temp;
            temp = temp->next;
        }
    
        if (temp == NULL) 
        {
            return node;
        }
        prev->next = temp->next;
        free(temp); 

        temp = prev->next;
    }
    return node;
    
}

