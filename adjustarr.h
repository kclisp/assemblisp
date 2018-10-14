#ifndef ADJUSTARR_H
#define ADJUSTARR_H

#include "types.h"

Adjustarr *init_adjustarr(char *start, size_t size);
void append(Adjustarr *mem, void *ptr, size_t size);

#endif
