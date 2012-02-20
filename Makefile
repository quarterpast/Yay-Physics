all: physics

physics: physics.c
	gcc -o physics physics.c -lm `pkg-config --cflags --libs glut` 
