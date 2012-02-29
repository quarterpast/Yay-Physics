UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CFLAGS=-framework OpenGL -framework GLUT
else
	CFLAGS=-Wall -g -lm -lglut -lGLU
endif

all:
	gcc -o PhysicsFork physics.c body.c vector.c $(CFLAGS)

clean:
	rm PhysicsFork
