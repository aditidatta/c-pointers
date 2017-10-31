#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

struct Node* createNode(char* name, int nameLength, void* data, int dataLength)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if(node == NULL)
    {
        return NULL;
    }
    node->nameLength = nameLength;
    node->dataLength = dataLength;
    node->name = (char*) malloc(nameLength+1);
    if(node->name == NULL)
    {
        free(node);
        node = NULL;
        return node;
    }
    strcpy(node->name, name);
    node->data = malloc(dataLength);
    if(node->data==NULL)
    {
        free(node->name);
        free(node);
        node = NULL;
        return node;
    }
    memcpy(node->data, data, dataLength);
    node->next = NULL;
    return node;
}

struct Node* destroyNode(struct Node* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    free(node->name);
    free(node->data);
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}

struct Node* copyNode(struct Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    struct Node* nodeCopy = (struct Node*) malloc(sizeof(struct Node));
    if(nodeCopy==NULL)
    {
        return nodeCopy;
    }
    nodeCopy->name = (char*) malloc(node->nameLength+1);
    if(nodeCopy->name == NULL)
    {
        free(nodeCopy);
        nodeCopy = NULL;
        return nodeCopy;
    }
    strcpy(nodeCopy->name, node->name);
    nodeCopy->data = malloc(node->dataLength);
    if(nodeCopy->data==NULL)
    {
        free(nodeCopy->name);
        free(nodeCopy);
        nodeCopy = NULL;
        return nodeCopy;
    }
    memcpy(nodeCopy->data, node->data, node->dataLength);
    nodeCopy->next = NULL;
    return nodeCopy;
}
