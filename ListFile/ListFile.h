
#ifndef LIST_FILE_H
#define LIST_FILE_H

#include "Node.h"

struct ListFile {
    int size;
    struct Node* head;
};

struct ListFile* makeList();
struct ListFile* copyList();
struct ListFile* destroyList(struct ListFile*);
void* findByName(struct ListFile*, char*);
int findByData(struct ListFile*, void*, int);
int removeByName(struct ListFile*, char*);
int removeByData(struct ListFile*, void*, int);
int insert(struct ListFile*, char*, void*, int);
struct ListFile* readFile(char*);
int appendFromFile(struct ListFile*, char*);
int saveToFile(struct ListFile*, char*);
void* getElement(struct ListFile*, int);
char* getElementName(struct ListFile*, int);
void traverse(struct ListFile*);

#endif