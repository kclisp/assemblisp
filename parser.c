#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "form.h"
#include "parser.h"

// Max atom length
#define BUF_SIZE 256
static char buf[BUF_SIZE];

/*
  Reads a lisp form from stream.
  Returns the corresponding Form.
  Returns NULL if there is no form.
*/
Form *read_form(FILE *stream) {
  // Go until you can determine whether the form is a list or atom
  // then use read_list or read_atom
  int c;
  while(isspace(c = getc(stream))) {}
  if (c == EOF)
    return NULL;

  if (c != '(' && !isalnum(c)) {
    printf("What is this? c: %c\n", c);
    return NULL;
  }
  
  Form *form = malloc(sizeof(Form));
  if (c == '(') {
    form->type = LIST;
    form->l = read_list(stream);
  } else {
    ungetc(c, stream);
    form->type = ATOM;
    form->a = read_atom(stream);
  }

  return form;
}

// Reads a list. ( is already read in stream
List *read_list(FILE *stream) {
  List *head = NULL;
  List *next;
  int c;
  for (;;) {
    c = getc(stream);
    
    if (c == EOF) {
      printf("EOF while reading a list!\n");
      break;
    }
    else if (isspace(c))
      continue;
    else if (c == ')')
      // one lisp form is read
      break;
    else {
      ungetc(c, stream);
      if (!head) {
        //first time then initialize head
        head = calloc(1, sizeof(List));
        head->data = read_form(stream);
        next = head;
      } else
        add_to_list(&next, read_form(stream));
    }
  }

  return head;
}

char *read_atom(FILE *stream) {
  // Read into buffer, keeping track of size.
  // Then malloc a string to fit those characters. Null terminate.
  int c;
  size_t size = 0;
  
  while (size < BUF_SIZE) {
    c = getc(stream);
    
    if (c == EOF)
      break;
    
    if (!isalnum(c)) {
      ungetc(c, stream);
      break;
    }
    buf[size] = (char)c;
    size++;
  }

  if (size >= BUF_SIZE)
    printf("Buffer size not big enough!");
  
  //add one for null
  char *str = malloc((size + 1) * sizeof(char));
  memcpy(str, buf, size);
  str[size] = 0;
  return str;
}

int main(int argc, char **argv) {
  Form *form = read_form(stdin);
  if (form) {
    print_form(form);
    printf("\n");
  } else
    printf("Null form!");
}
