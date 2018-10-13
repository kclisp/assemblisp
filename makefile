DEPS = interp.h types.h form.h parser.h
OBJ = interp.o form.o parser.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

interp: $(OBJ)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ */*~ interp
