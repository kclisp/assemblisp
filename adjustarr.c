#include <string.h>
#include "adjustarr.h"

Adjustarr *init_adjustarr(char *start, size_t size) {
  Adjustarr *new = malloc(sizeof(Adjustarr));
  new->start = start;
  new->at = start;
  new->size = size;
  return new;
}

void append(Adjustarr *mem, void *ptr, size_t size) {
  while ((mem->at + size) >= (mem->start + mem->size)) {
    mem->start = realloc(mem->start, 2 * mem->size);
    //zero out
    memset(mem->at, 0, mem->start + mem->size - mem->at);
    mem->size *= 2;
  }
  memcpy(mem->at, ptr, size);
  mem->at += size;
}
