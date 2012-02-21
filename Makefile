ifneq (,)
This makefile requires GNU Make.
endif

PROGRAM=physics

CC=gcc
CFLAGS=-g -lm `pkg-config --cflags --libs glut`
C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))

.SUFFIXES: .c .o

all: clean $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(PROGRAM) *.o

.PHONY: clean