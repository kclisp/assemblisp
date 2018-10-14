#include <stdio.h>
#include <string.h>
#include "adjustarr.h"
#include "assembler.h"
#include "interp.h"
/// Interpreter for assemblisp

#define INIT_MEM_SIZE 1024
//keep track of the block of memory where the code is being stored
Adjustarr *code_memory;
//keep track of labels
Adjustarr *env;

// initializing code for the interpreter
void init_interpret() {
  code_memory = init_adjustarr(calloc(1, INIT_MEM_SIZE), INIT_MEM_SIZE);
  env = init_adjustarr(calloc(1, INIT_MEM_SIZE), INIT_MEM_SIZE);
}

/* Given lisp form:
   if first arg is assembly opcode, write corresponding values into memory.
   if label, store address at that point under corresponding name in env
   [if macro, macroexpand]
*/
// interpret single lisp form
void interpret(Form *form) {
  if (form->type == ATOM) {
    printf("Top level form is an atom...\n");
    return;
  }
  if (form->l->data->type == LIST) {
    printf("Top level form is a list of list...\n");
    return;
  }
  if (is_mnemonic(form)) {
    write_opcode(code_memory, env, form);
  } else if (strcmp(form->l->data->a, "label")) {
    //should use hashtable eventually
    append(env, &form->l->next->data->a, sizeof(char *));
    append(env, &code_memory->at, sizeof(char *));
  } else {
    printf("Don't know what to do with %s yet...\n", form->l->data->a);
  }
}

/* macroexpand: compile macro, but leave args as pointing to the stack
   Then, when a macro is seen, call to that macro in memory just like a function
   Then return value is put back.
 */
int main(int argc, char **argv) {

}
