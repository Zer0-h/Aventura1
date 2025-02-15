CC=gcc # compilador
CFLAGS=-c -g -Wall -std=c99 #flags para el compilador
LDFLAGS= #flags para enlazador

SOURCES=my_lib.c test1.c test2.c test1breve.c
LIBRARIES=my_lib.o 
INCLUDES=my_lib.h
PROGRAMS=test1 test2 test1breve
OBJS=$(SOURCES:.c=.o)

all: $(OBJS) $(PROGRAMS)

#$(PROGRAMS): $(LIBRARIES) $(INCLUDES)
#	$(CC) $(LDFLAGS) $(LIBRARIES) $@.o -o $@

test1: test1.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

test1breve: test1breve.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@


test2: test2.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o $(PROGRAMS)
