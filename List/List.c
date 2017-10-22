#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "List.h"

struct Node 
{
    int data;
    struct Node* next;
};

struct Node* constructList(int elem)
{
    struct Node* node = malloc(sizeof(struct Node));
    node->data = elem;
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

struct Node* insert(struct Node *node, int elem)
{
    struct Node* newNode = NULL;
    struct Node* temp = node;
    
    if(node == NULL)
    {
        newNode = constructList(elem);
        return newNode;
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = constructList(elem);
        temp = NULL;
        return node;
    }
}

int find(struct Node* node, int elem)
{
    struct Node* temp = node;
    int found = 0;
    while(temp!=NULL)
    {
        if(temp->data == elem)
        {
            found = 1;
            break; 
        }
        temp = temp->next;
    }
    temp = NULL;
    return found;
}

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
            sprintf(str+currPos, "%d", temp->data);
        }
        else
        {
            sprintf(str+currPos, "%d,", temp->data);
        }
        temp = temp->next;
        currPos = strlen(str);
    }
    
    char* buffer = (char *)malloc(currPos+1);
    strcpy(buffer,str);
    free(str);
    return buffer;
}

int traverse(struct Node *node, char *str)
{
    struct Node* temp = node;
    char* buffer = str;
    int count = 0;
    while(temp!=NULL)
    {
        count++;
        if(temp->next == NULL)
        {
            sprintf(buffer, "%d", temp->data);
        }
        else
        {
            sprintf(buffer, "%d,", temp->data);
        }
        temp = temp->next;
        buffer = buffer + strlen(buffer);
        //printf("\n%s\n", str);
    }
    return count;
}

struct Node* removeItem(struct Node *node, int elem)
{
    struct Node* temp = NULL;
    struct Node* prev = NULL;
    if(node == NULL)
    {
        return node;
    }
       
    while (temp != NULL && temp->data == elem)
    {
        node = temp->next;   
        free(temp);           
        temp = node;
    }
    
       
    while (temp != NULL)
    {
        while (temp != NULL && temp->data != elem)
        {
            prev = temp;
            temp = temp->next;
        }
    
        if (temp == NULL) 
        {
            return NULL;
        }
        prev->next = temp->next;
        free(temp); 
        temp = prev->next;
    }
    return node;
    
}

