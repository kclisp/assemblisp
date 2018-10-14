#ifndef FORM_H
#define FORM_H

#include "types.h"

void add_to_list(List **next, Form *data);
void free_form(Form *form);
void print_form(Form *form);

#endif
