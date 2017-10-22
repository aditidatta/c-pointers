#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Alloc.h"
#include "List.h"

struct Alloc
{
    void* memory;
    size_t capacity;
    size_t used_size;
    size_t num_allocations;
    struct Node* allocations;
    struct Node* free_blocks;
    int need_deallocate;
};

struct Alloc* constructAlloc(size_t sz)
{
    if(sz < 0)
    {
        return NULL;
    }
    struct Alloc* alloc = (struct Alloc *) malloc(sizeof(struct Alloc));
    if(alloc == NULL)
    {
        return NULL;
    }
    sz = (sz + 15) & ~15;
    alloc->capacity = sz;
    alloc->used_size = 0;
    alloc->num_allocations = 0;
    alloc->allocations = NULL;
    alloc->free_blocks = NULL;
    alloc->need_deallocate = 0;
    alloc->memory = malloc(sz);
    if(alloc->memory == NULL)
    {
        free(alloc);
        alloc = NULL;
    }
    else
    {
        alloc->free_blocks = constructList(alloc->memory, alloc->capacity);
        //printf("\n%ld\n",alloc->free_blocks->size);
    }
    return alloc;
}

struct Alloc* destroyAlloc(struct Alloc *alloc)
{
    if(alloc != NULL)
    {
        free(alloc->memory);
        destroyList(alloc->allocations);
        destroyList(alloc->free_blocks);
        free(alloc);
        alloc = NULL;
    }
    return alloc;
}

void print(struct Node* list)
{
    char *buffer = (char *)calloc(1, 1000 * sizeof(char));
    if(traverse2(list, buffer) == 0)
    {
        fprintf(stderr, "[].\n\n");
    }
    else
    {
        fprintf(stderr, "[%s].\n\n", buffer);
    }

    free(buffer);

}

void* allocate(struct Alloc *alloc, size_t sz)
{
    if (alloc == NULL)
    {
        return NULL;
    }
    sz = (sz + 15) & ~15;
    //fprintf(stderr,"%ld\n",sz);
    if(alloc->used_size+sz > alloc->capacity)
    {
        return NULL;
    }
    struct Node* node = findBySize(alloc->free_blocks,sz);
    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        void *ptr = node->ptr;
        fprintf(stderr, "Allocating %ld\n", sz);
        alloc->allocations = insert(alloc->allocations, ptr, sz);
        alloc->num_allocations++;
        void *next_ptr = (void*)(((char*)ptr)+sz);
        size_t remaining_space = node->size-sz;
        alloc->free_blocks = removeItem(alloc->free_blocks, ptr);
        if(remaining_space != 0)
        {
            alloc->free_blocks = insert(alloc->free_blocks, next_ptr, remaining_space);
            //size_t test = size(alloc->free_blocks);
            //fprintf(stderr,"%ld\n", test);
        }
        alloc->used_size += sz;
        node = NULL;
        fprintf(stderr,"Allocations: ");
        print(alloc->allocations);
        fprintf(stderr,"Free blocks: ");
        print(alloc->free_blocks);
        return ptr;
    }   
}

void assignFreeBlock(struct Node** free_blocks_list, void* ptr, size_t sz)
{
    struct Node* left = NULL;
    struct Node* right = NULL;
    struct Node* node = *free_blocks_list;
    size_t total_size = sz;
    while(node != NULL)
    {
        if(right == NULL && node->ptr == (void*)(((char*)ptr)+sz))
        {
            right = node;
        }
        if(left == NULL && ptr == (void*)(((char*)node->ptr)+node->size))
        {
            left = node;
        }

        if(right != NULL && left != NULL)
        {
            break;
        }
        node = node->next;
    }

    if(right!=NULL)
    {
        total_size += right->size;
        *free_blocks_list = removeItem(*free_blocks_list, right->ptr);
    }
    if(left != NULL)
    {
        total_size += left->size;
        ptr = left->ptr;
        *free_blocks_list = removeItem(*free_blocks_list, left->ptr);
    }

    *free_blocks_list = insert(*free_blocks_list, ptr, total_size);

    free_blocks_list = NULL;
    left = NULL;
    right = NULL;

}

void deallocate(struct Alloc *alloc, void *ptr)
{
    fprintf(stderr,"\nDeallocating: %p\n", ptr);
    if(alloc != NULL)
    {
        if(ptr != NULL)
        {
            struct Node* node = find(alloc->allocations, ptr);
            if (node == NULL)
            {
                fprintf(stderr, "\nCorruption in free\n");
                exit(2);
            }
            else
            {
                void* ptr = node->ptr;
                size_t sz = node->size;
                //fprintf(stderr, "Ret size: %ld\n", sz);
                /*
                void* next = (void*)(((char*)ptr)+sz);
                struct Node* f = find(alloc->free_blocks, next);
                if (f == NULL)
                {
                    alloc->free_blocks = insert(alloc->free_blocks, ptr, sz);
                }
                else
                {
                    f->ptr = ptr;
                    f->size = f->size+sz;
                }
                */
                assignFreeBlock(&(alloc->free_blocks), ptr, sz);
                alloc->allocations = removeItem(alloc->allocations, ptr);
                alloc->num_allocations--;
                alloc->used_size -= sz;
                //f = NULL;
                ptr = NULL;
                //fprintf(stderr, "Used size: %ld\n", alloc->used_size);
            }
            node = NULL;
        }
    }
    fprintf(stderr,"Allocations: ");
    print(alloc->allocations);
    fprintf(stderr,"Free blocks: ");
    print(alloc->free_blocks);
}

size_t getCapacity(struct Alloc *alloc)
{
    if(alloc == NULL)
    {
        return 0;
    }
    return alloc->capacity;
}

size_t getSize(struct Alloc *alloc)
{
    if(alloc == NULL)
    {
        return 0;
    }
    return alloc->used_size;
}

void* getBase(struct Alloc *alloc)
{
    if(alloc == NULL)
    {
        return NULL;
    }
    return alloc->memory;
}

size_t getNumAllocations(struct Alloc *alloc)
{
    if(alloc == NULL)
    {
        return 0;
    }
    //return size(alloc->allocations);
    return alloc->num_allocations;
}

void** getAllocations(struct Alloc *alloc)
{
    void** l = traverse(alloc->allocations);
    return l;
}

int needDeallocate(struct Alloc *alloc)
{
    if(alloc == NULL)
    {
        return 1;
    }
    return alloc->need_deallocate;
}

void rearrange(struct Node* node, void* old, void* new)
{
    while(node!=NULL)
    {
        size_t offset = node->ptr - old;
        node->ptr = new+offset;
        node = node->next;
    }
}

void* riskyAlloc(struct Alloc *alloc, size_t size)
{
    if(alloc == NULL)
    {
        return NULL;
    }
    void* mem = realloc(alloc->memory,size);
    if(mem == NULL)
    {
        destroyAlloc(alloc);
        fprintf(stderr, "\nBad Memory\n");
        exit(3);
        return NULL;
    }
    else
    {
        void* old_ptr = alloc->memory;
        alloc->memory = mem;
        alloc->capacity = size;
        rearrange(alloc->allocations, old_ptr, mem);
        rearrange(alloc->free_blocks, old_ptr, mem);
        alloc->need_deallocate = 1;
        return alloc->memory;
    }
}