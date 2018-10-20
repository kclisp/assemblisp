#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include "uthash.h"

struct List {
  struct Form *data;
  struct List *next;
};

//Form is either a list or an atom
enum Type {LIST, ATOM};
struct Form {
  enum Type type;
  union {
    struct List *l;
    char *a;
  };
};

//executable memory block
struct Memblock {
  char *start;
  char *at;
  size_t size;
};

//an environment entry
struct Env_entry {
  char *name;    //key
  char *ptr;     //val
  UT_hash_handle hh;    //make it hashable
};
  
typedef struct List List;
typedef struct Form Form;
typedef struct Memblock Memblock;
typedef struct Env_entry Env_entry;

#endif
