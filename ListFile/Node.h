#ifndef NODE_H
#define NODE_H

struct Node {
    char* name;
    int nameLength;
    void* data;
    int dataLength;
    struct Node* next;
};

struct Node* createNode(char*, int, void*, int);
struct Node* copyNode(struct Node*);
struct Node* destroyNode(struct Node*);

#endif