#ifndef COMPILER_H
#define COMPILER_H

#include "types.h"

void init_compiler();
void compile(Form *form);
void write_bytes(List *list);

#endif
