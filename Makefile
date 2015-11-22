CC := mpic++
CFLAGS := -g -O2 -std=c++11

.PHONY: all run clean

all: main

main: main_p.cpp filter.hpp image.hpp reader.hpp convolution.hpp writer.hpp
	$(CC) $(CFLAGS) -o $@ $<

run: main
	./$<

clean:
	rm -f *.o main
