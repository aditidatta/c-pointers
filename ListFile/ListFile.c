#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListFile.h"

struct ListFile* makeList()
{
    struct ListFile* list = (struct ListFile*) malloc(sizeof(struct ListFile));
    if(list == NULL)
    {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

struct ListFile* copyList(struct ListFile* list)
{
    if(list == NULL)
    {
        return NULL;
    }
    struct ListFile* listCopy = makeList();
    if(listCopy == NULL)
    {
        return listCopy;
    }
    struct Node* temp1 = list->head;
    //struct Node* temp2 = listCopy->head;
    /*
    if(temp1 != NULL)
    {
        temp2 = copyNode(temp1);
        temp1 = temp1->next;
    }

    while(temp1 != NULL)
    {
        if(temp2 == NULL)
        {
            // error
            destroyList(listCopy);
            listCopy = NULL;
            return listCopy;
        }
        temp2->next = copyNode(temp1);
        temp2 = temp2->next;
        temp1 = temp1->next;
    }*/
    while(temp1!=NULL)
    {
        insert(listCopy, temp1->name, temp1->data, temp1->dataLength);
        temp1=temp1->next;
    }
    listCopy->size = list->size;
    return listCopy;
}

struct ListFile* destroyList(struct ListFile* list)
{
    if(list == NULL)
    {
        return NULL;
    }
    struct Node* temp = list->head;
    
    while(temp != NULL)
    {
        struct Node* next = temp->next;
        destroyNode(temp);
        temp = next;
    }
    free(list);
    list = NULL;
    return list;
}

int insert(struct ListFile* list, char* name, void* data, int length)
{
    if(list == NULL)
    {
        return 0;
    }
    struct Node* temp = list->head;
    if(temp == NULL)
    {
        struct Node* newNode = createNode(name, strlen(name), data, length);
        if(newNode == NULL)
        {
            return 0;
        }
        list->head = newNode;
        list->size = 1;
        return 1;
    }
    if (temp!=NULL)
    {
        int res = strcmp(name, temp->name);
        if(res == 0)
        {
            return 0;
        }
        if(res < 0)
        {
            struct Node* newNode = createNode(name, strlen(name), data, length);
            if(newNode == NULL)
            {
                return 0;
            }
            newNode->next = temp;
            list->head = newNode;
            list->size++;
            return 1;
        }
    }
    struct Node* prev = list->head;
    temp = list->head->next;
    while(temp!=NULL)
    {
        int res = strcmp(name, temp->name);
        if(res == 0)
        {
            return 0;
        }
        if(res < 0)
        {
            break;
        }
        temp = temp->next;
        prev = prev->next;
    }

    struct Node* newNode = createNode(name, strlen(name), data, length);
    if(newNode == NULL)
    {
        return 0;
    }
    newNode->next = temp;
    prev->next = newNode;
    list->size++;
    return 1;
}

void* findByName(struct ListFile* list, char* name)
{
    if(list == NULL)
    {
        return NULL;
    }
    struct Node* temp = list->head;
    while(temp!=NULL)
    {
        int res = strcmp(temp->name, name);
        if(res == 0)
        {
            return temp->data;
        }
        temp = temp->next;
    }
    return NULL;
}

int findByData(struct ListFile* list, void* data, int length)
{
    if(list == NULL)
    {
        return 0;
    }

    int count = 0;
    struct Node* temp = list->head;

    while(temp!=NULL)
    {
        if(temp->dataLength == length)
        {
            int res = memcmp(data, temp->data, length);
            if(res == 0)
            {
                count++;
            }
        }
        temp = temp->next;
    }

    return count;
}

int removeByName(struct ListFile* list, char* name)
{
    if(list == NULL)
    {
        return 0;
    }
    struct Node* temp = list->head;
    if(temp != NULL && strcmp(temp->name, name) == 0)
    {
        list->head = temp->next;
        destroyNode(temp);
        list->size -= 1;
        return 1;
    }
    struct Node* prev = list->head;
    temp = list->head->next;
    while(temp!=NULL)
    {
        int res = strcmp(temp->name, name);
        if(res == 0)
        {
            prev->next = temp->next;
            destroyNode(temp);
            list->size -= 1;
            return 1;
        }
        prev = prev->next;
        temp = temp->next;
    }
    return 0;
}

int removeByData(struct ListFile* list, void* data, int length)
{
    if(list == NULL)
    {
        return 0;
    }
    if(data == NULL)
    {
        return 0;
    }
    int count = 0;

    struct Node* temp = list->head;
    while(temp != NULL && temp->dataLength == length && memcmp(data, temp->data, length) == 0)
    {
        
        list->head = temp->next;
        destroyNode(temp);
        temp = list->head;
        count++;
    }
    struct Node* prev = list->head;
    temp = list->head->next;
    while(temp!=NULL)
    {
        if(temp->dataLength == length && memcmp(data, temp->data, length) == 0)
        {
            prev->next = temp->next;
            destroyNode(temp);
            count++;
            if(prev->next != NULL)
            {
                temp = prev->next;
            }
            else
            {
                temp = NULL;
            }
        }
        else
        {
            prev = prev->next;
            temp = temp->next;
        }   
    }
    list->size -= count;
    return count;
}

struct ListFile* readFile(char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        return NULL;
    }
    char num[5];
    fread(num, 4, 1, fp);
    int numElem = atoi(num);
    int count = 0;
    struct ListFile* list = makeList();

    while(count < numElem)
    {
        fread(num, 4, 1, fp);
        int nameLength = atoi(num);
        fread(num, 4, 1, fp);
        int dataLength = atoi(num);
        char* buf1 = (char*)malloc(nameLength+1);
        fread(buf1, nameLength, 1, fp);
        void* buf2 = malloc(dataLength);
        fread(buf2, dataLength, 1, fp);
        insert(list, buf1, buf2, dataLength);
        count++;
    }
    fclose(fp);
    return list;
}

int appendFromFile(struct ListFile* list, char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        return -1;
    }
    char num[5];
    fread(num, 4, 1, fp);
    int numElem = atoi(num);
    int count = 0;
    int insertCount = 0;

    while(count < numElem)
    {
        fread(num, 4, 1, fp);
        int nameLength = atoi(num);
        fread(num, 4, 1, fp);
        int dataLength = atoi(num);
        char* buf1 = (char*)malloc(nameLength+1);
        fread(buf1, nameLength, 1, fp);
        void* buf2 = malloc(dataLength);
        fread(buf2, dataLength, 1, fp);
        int res = insert(list, buf1, buf2, dataLength);
        if(res != 0)
        {
            insertCount++;
        }
        count++;
    }
    fclose(fp);
    return insertCount;
}

int saveToFile(struct ListFile* list, char* filename)
{
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL)
    {
        return -1;
    }
    /*
    if(list == NULL)
    {
        fclose(fp);
        return -1;
    }
    */
    fwrite(&(list->size), sizeof(int), 1, fp);
    int count = 0;
    struct Node* temp = list->head;
    while(count < list->size)
    {
        fwrite(&(temp->nameLength), sizeof(int), 1, fp);
        fwrite(&(temp->dataLength), sizeof(int), 1, fp);
        fwrite(temp->name, temp->nameLength, 1, fp);
        fwrite(temp->data, temp->dataLength, 1, fp);
        temp = temp->next;
        count++;
    }
    fclose(fp);
    return 0;
}

void* getElement(struct ListFile* list, int index)
{
    if(list == NULL)
    {
        return NULL;
    }
    struct Node* temp = list->head;
    int count = 0;
    while(temp!=NULL)
    {
        if(count == index)
        {
            return temp->data;
        }
        temp = temp->next;
    }

    return NULL;
}

char* getElementName(struct ListFile* list, int index)
{
    if(list == NULL)
    {
        return NULL;
    }
    struct Node* temp = list->head;
    int count = 0;
    while(temp!=NULL)
    {
        if(count == index)
        {
            return temp->name;
        }
        temp = temp->next;
    }

    return NULL;
}

void traverse(struct ListFile* list)
{
    if(list == NULL)
    {
        return;
    }
    struct Node* temp = list->head;
    int count = 0;
    while(temp!=NULL)
    {
        fprintf(stderr, "Node %2d: Name Length - %2d, Name - %5s, Data length - %2d\n", count, temp->nameLength, temp->name, temp->dataLength);
        temp = temp->next;
    }
}
