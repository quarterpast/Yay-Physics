ifneq (,)
This makefile requires GNU Make.
endif

PROGRAM=physics
UNAME := $(shell uname)

CC=gcc
ifeq ($(UNAME), Darwin)
	CFLAGS=-framework OpenGL -framework GLUT
else
	CFLAGS=-g -lm `pkg-config --cflags --libs glut`
endif
C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))

.SUFFIXES: .c .o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(PROGRAM) *.o

.PHONY: clean
