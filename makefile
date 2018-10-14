DEPS = interp.h types.h form.h parser.h adjustarr.h assembler.h
OBJ = interp.o form.o parser.o adjustarr.o assembler.c

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

interp: $(OBJ)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ */*~ interp
