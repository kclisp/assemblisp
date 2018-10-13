#ifndef PARSER_H
#define PARSER_H

Form *read_form(FILE *stream);
List *read_list(FILE *stream);
char *read_atom(FILE *stream);

#endif
