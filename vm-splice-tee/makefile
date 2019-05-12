CC=gcc
CFLAGS=-I.
# DEPS = vm-t-splice.h
OBJ = vm-t-splice.o 
LIBS=-lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vm-t-splice: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# run: vm-t-splice
#     time ./vm-t-splice

clean:
	rm -f vm-t-splice vm-t-splice.o