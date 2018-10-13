/// Interpreter for assemblisp


/* Given lisp form:
   if first arg is assembly opcode, write corresponding values into memory.
   if label, store address at that point under corresponding name
   if special, do special things
   [if macro, macroexpand]
*/

