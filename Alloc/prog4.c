#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Alloc.h"

void printDetails(struct Alloc *alloc)
{
    size_t cap = getCapacity(alloc);
    fprintf(stderr, "Capacity   : %ld \n", cap);
    size_t sz = getSize(alloc);
    fprintf(stderr, "Used Size  : %ld \n", sz);
    void* base = getBase(alloc);
    fprintf(stderr, "Base       : %p \n", base);
    size_t num = getNumAllocations(alloc);
    fprintf(stderr, "Num Alloc  : %ld \n\n", num);
    
}

void printArrOfPtr(void** arr, size_t num)
{
    if(arr==NULL)
    {
        fprintf(stderr, "\nNo allocations yet...\n");
        return;
    }
    fprintf(stderr, "\nAll allocations: ");
    size_t i;
    for(i = 0; i < num; i++)
    {
        fprintf(stderr, "%p, ", arr[i]);
    }
    fprintf(stderr, "\n");
}

int main(int args, char** argv)
{
    struct Alloc* alloc = constructAlloc(160);
    /*if (alloc == NULL)
    {
        fprintf(stderr, "\nAllocation not successful...\n");
        return 2;
    }*/
    fprintf(stderr, "\nSuccessfully allocated...\n");
    printDetails(alloc);
    void* ptr = allocate(alloc, 160);
    deallocate(alloc, ptr);

    void* ptr1 = allocate(alloc, 16);
    void* ptr2 = allocate(alloc, 16);
    void* ptr3 = allocate(alloc, 32);
    void* ptr4 = allocate(alloc, 16);
    void* ptr5 = allocate(alloc, 32);
    void* ptr6 = allocate(alloc, 16);
    printDetails(alloc);
    size_t num = getNumAllocations(alloc);
    void** arr = getAllocations(alloc);
    printArrOfPtr(arr, num);
    free(arr);

    fprintf(stderr, "\nDeallocating some pointers...\n\n");
    deallocate(alloc, ptr1);
    deallocate(alloc, ptr3);
    deallocate(alloc, ptr2);
    deallocate(alloc, ptr5);

    printDetails(alloc);
    num = getNumAllocations(alloc);
    arr = getAllocations(alloc);
    printArrOfPtr(arr, num);
    free(arr);
    
    destroyAlloc(alloc);
    alloc = NULL;
    printDetails(alloc);
    
    return 0;
}