#include <stdlib.h>
#include <stdio.h>
#include "form.h"

// Updates next with data
// Then updates next to be the next (newly malloced) list.
void add_to_list(List **next, Form *data) {
  List *new_list = calloc(1, sizeof(List));
  
  (*next)->next = new_list;
  *next = new_list;
  new_list->data = data;
}

void print_form(Form *form) {
  if (!form)
    return;
  if (form->type == ATOM)
    printf("%s", form->a);
  else {
    // done this way for proper spacing
    List *next = form->l;
    printf("(");
    if (next) {
      print_form(next->data);
      for (next = next->next; next; next = next->next) {
        printf(" ");
        print_form(next->data);
      }
    }
    printf(")");
  }
}
