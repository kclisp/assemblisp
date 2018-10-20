#define _GNU_SOURCE

#include <sys/mman.h>
#include <string.h>
#include "memblock.h"

//allocates memory and marks as executable
Memblock *init_memblock(size_t size) {
  Memblock *new = malloc(sizeof(Memblock));
  new->start = mmap(NULL, size,
                    PROT_READ | PROT_WRITE | PROT_EXEC,
                    MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
  new->at = new->start;
  new->size = size;
  return new;
}

//automatically extends memory region if necessary
void append(Memblock *mem, void *ptr, size_t size) {
  while ((mem->at + size) >= (mem->start + mem->size))
    extend(mem);
  memcpy(mem->at, ptr, size);
  mem->at += size;
}

void extend(Memblock *mem) {
  //need this because start could move due to mremap
  unsigned dif = mem->at - mem->start;
  
  mem->start = mremap(mem->start, mem->size, 2 * mem->size, MREMAP_MAYMOVE);
  mem->at = mem->start + dif;
  
  //zero out
  memset(mem->at, 0, mem->start + mem->size - mem->at);
  mem->size *= 2;
}
