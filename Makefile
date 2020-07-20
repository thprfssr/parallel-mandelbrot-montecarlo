CC = gcc
flags = -lm -fopenmp
objects = test.o
targets = test

all: $(targets)
	make $(targets)

test: $(objects)
	$(CC) $(flags) -o $@ $(objects)


test.o:

.PHONY: clean
clean:
	rm $(targets) $(objects)
