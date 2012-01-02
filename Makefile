CFLAGS=-Wall -pedantic -O3 -std=c99

solve: solve.c data.h convert.h

gen: gen.c convert.h

data.h:	gen
	gen > data.h

clean:
	rm gen solve data.h
