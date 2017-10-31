#include <stdio.h>
#include <stdlib.h>
#include "ListFile.h"

int main()
{
    char* name1 = "hello";
    char* name2 = "coffee";
    char* name3 = "marshmallow";
    int dataLength1 = 3;
    int dataLength2 = 3;
    int dataLength3 = 4;

    void* data1 = malloc(dataLength1);
    void* data2 = malloc(dataLength2);
    void* data3 = malloc(dataLength3);

    struct ListFile* list = makeList();
    insert(list, name1, data1, dataLength1);
    fprintf(stderr, "size: %d\n", list->size);
    insert(list, name2, data2, dataLength2);
    fprintf(stderr, "size: %d\n", list->size);
    insert(list, name3, data3, dataLength3);
    fprintf(stderr, "size: %d\n", list->size);

    traverse(list);
    void* data = findByName(list, "hello");
    if(data != NULL)
    {
        fprintf(stderr, "Found data by name hello\n");
    }

    struct ListFile* list3 = copyList(list);
    data = findByName(list3, "hello");
    if(data != NULL)
    {
        fprintf(stderr, "Found data by name hello in list 3\n");
    }

    saveToFile(list, "output.0");
    struct ListFile* list2 = readFile("output.0");
    data = findByName(list2, "hello");
    if(data != NULL)
    {
        fprintf(stderr, "Found data by name hello in List 2\n");
    }
    int count = findByData(list2, data3, dataLength3);

    fprintf(stderr, "Found by data in list 2: %d\n", count);

    removeByName(list, "coffee");
    fprintf(stderr, "after remove size: %d\n", list->size);

    removeByData(list, data1, dataLength1);
    fprintf(stderr, "after remove size: %d\n", list->size);
    destroyList(list);
    destroyList(list2);
    destroyList(list3);
    free(data1);
    free(data2);
    free(data3);
    return 0;
}