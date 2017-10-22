#ifndef ALLOC_ALLOC_H
#define ALLOC_ALLOC_H

struct Alloc* constructAlloc(size_t size);
struct Alloc* destroyAlloc(struct Alloc *alloc);
void* allocate(struct Alloc *alloc, size_t size);
void deallocate(struct Alloc *alloc, void *ptr);
size_t getCapacity(struct Alloc *alloc);
size_t getSize(struct Alloc *alloc);
void* getBase(struct Alloc *alloc);
size_t getNumAllocations(struct Alloc *alloc);
void** getAllocations(struct Alloc *alloc);
int needDeallocate(struct Alloc *alloc);
void* riskyAlloc(struct Alloc *alloc, size_t size);

#endif