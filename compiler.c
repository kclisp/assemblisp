#include <stdio.h>
#include <string.h>
#include "adjustarr.h"
#include "assembler.h"
#include "parser.h"
#include "form.h"
#include "compiler.h"
/// Compiler for assemblisp

#define INIT_MEM_SIZE 1024
//keep track of the block of memory where the code is being stored
Adjustarr *code_mem;
//keep track of labels
Adjustarr *env;

// initializing code for the compiler
void init_compiler() {
  code_mem = init_adjustarr(calloc(1, INIT_MEM_SIZE), INIT_MEM_SIZE);
  env = init_adjustarr(calloc(1, INIT_MEM_SIZE), INIT_MEM_SIZE);
}

/* Given lisp form:
   if first arg is assembly opcode, write corresponding values into memory.
   if label, store address at that point under corresponding name in env
   if special, do special things
   [if macro, macroexpand]
*/
// compile single lisp form
void compile(Form *form) {
  if (form->type == ATOM) {
    printf("Top level form is an atom...\n");
    return;
  }
  if (form->l->data->type == LIST) {
    printf("Top level form is a list of list...\n");
    return;
  }
  
  char *atom = form->l->data->a;
  if (is_mnemonic(form)) {
    write_opcode(form);
  } else if (strcmp(atom, "label") == 0) {
    //should use hashtable eventually
    append(env, &form->l->next->data->a, sizeof(char *));
    append(env, &code_mem->at, sizeof(char *));
  } else if (strcmp(atom, "bytes") == 0) {
    write_bytes(form->l->next);
  } else {
    printf("Don't know what to do with %s yet...\n", atom);
  }
}

//write the bytes contained in list to code_mem
//each atom in list is a single byte in string form
void write_bytes(List *list) {
  long int l;
  for (; list; list = list->next) {
    // sanity check
    if (list->data->type != ATOM) {
      printf("Type in bytes is not an atom!\n");
      return;
    }
    l = strtol(list->data->a, NULL, 16);
    append(code_mem, &l, 1);
  }
}

/* macroexpand: compile macro, but leave args as pointing to the stack
   Then, when a macro is seen, call to that macro in memory just like a function
   Then return value is put back.
 */

void print_code_mem () {
  char *ptr;
  for (ptr = code_mem->start; ptr < code_mem->at; ptr++)
    printf("%x ", *ptr);
}

int main(int argc, char **argv) {
  init_compiler();
  print_code_mem();
  Form *form = read_form(stdin);
  print_form(form);
  printf("\n");
  compile(form);
  print_code_mem();
}
