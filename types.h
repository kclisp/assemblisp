#ifndef TYPES_H
#define TYPES_H

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

typedef struct List List;
typedef struct Form Form;

#endif
