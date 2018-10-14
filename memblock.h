#ifndef ADJUSTARR_H
#define ADJUSTARR_H

#include "types.h"

Memblock *init_memblock(size_t size);
void append(Memblock *mem, void *ptr, size_t size);

#endif
