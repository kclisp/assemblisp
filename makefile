DEPS = compiler.h types.h form.h parser.h memblock.h assembler.h env.h
OBJ = compiler.o form.o parser.o memblock.o assembler.o env.o
EXEC = compiler

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

$(EXEC): $(OBJ)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ */*~ $(EXEC)
