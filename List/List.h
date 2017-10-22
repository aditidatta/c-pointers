#ifndef LIST_LIST_H
#define LIST_LIST_H

//typedef struct Node* Node;

// Constructors-Destructors ---------------------------------------------------
struct Node* constructList(int);
struct Node* destroyList(struct Node*);
size_t size(struct Node*);
struct Node* insert(struct Node*, int);
int find(struct Node*, int);
int traverse(struct Node*, char *);
struct Node* removeItem(struct Node*, int);
char* traverse2(struct Node*);

#endif //LIST_LIST_H
