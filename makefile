DEPS = compiler.h types.h form.h parser.h adjustarr.h assembler.h
OBJ = compiler.o form.o parser.o adjustarr.o assembler.c
EXEC = compiler

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

$(EXEC): $(OBJ)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ */*~ $(EXEC)
