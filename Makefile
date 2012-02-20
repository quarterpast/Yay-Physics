all: physics

physics: physics.c
	gcc -lm `pkg-config --cflags --libs glut` -o physics physics.c
