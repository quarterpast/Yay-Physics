all: physics

physics: physics.c
	gcc -o physics physics.c -g -lm `pkg-config --cflags --libs glut` 
