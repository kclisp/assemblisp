DEPS = compiler.h types.h form.h parser.h memblock.h assembler.h
OBJ = compiler.o form.o parser.o memblock.o assembler.c
EXEC = compiler

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

$(EXEC): $(OBJ)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ */*~ $(EXEC)
