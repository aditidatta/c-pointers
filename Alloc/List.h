#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdio.h>
//#include <stdlib.h>

struct Node 
{
    void* ptr;
    size_t size;
    struct Node* next;
};

// Constructors-Destructors ---------------------------------------------------
struct Node* constructList(void*, size_t);
struct Node* destroyList(struct Node*);
size_t size(struct Node*);
struct Node* insert(struct Node*, void*, size_t);
struct Node* find(struct Node*, void *);
struct Node* findBySize(struct Node*, size_t);
void** traverse(struct Node*);
int traverse2(struct Node *node, char *str);
struct Node* removeItem(struct Node*, void*);
//char* traverse2(struct Node*);

#endif //LIST_LIST_H
