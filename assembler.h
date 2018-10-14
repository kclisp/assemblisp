#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "types.h"

int is_mnemonic(Form *form);
void write_opcode(Adjustarr *mem, Adjustarr *env, Form *form);


#endif
