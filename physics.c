#include "physics.h"

Body *b;
int bodies;
double steps = 2.0;
int width = WIDTH;
int height = HEIGHT;
int oldwidth = WIDTH;
int oldheight = HEIGHT;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Yay physics");

	srand(time(NULL));
	if(argc < 2) return 1;

	bodies = atoi(argv[1]);
	b = malloc(bodies*sizeof(Body));
	int i;
	//b[0] = newBody(newVector(0,0.0001),newVector(0,0),1000);
	for(i=0;i<bodies;++i) {
		b[i] = newBody(newVector(
			1-2*(float)rand()/(float)RAND_MAX,
			1-2*(float)rand()/(float)RAND_MAX
		),
		newVector(
			0.002-0.004*(float)rand()/(float)RAND_MAX,
			0.002-0.004*(float)rand()/(float)RAND_MAX
		),100*(float)rand()/(float)RAND_MAX);
	}

	glutDisplayFunc(step);
	glutTimerFunc(TIMERMSECS, step, 0);
	glutKeyboardFunc(keyPressed);
	glutReshapeFunc(reshape);

	glutMainLoop();
}


/* GL/GLUT stuff */
void keyPressed (unsigned char key, int x, int y) {
	printf("%c\n",key);
	if(key == 'f') {
		#ifdef __FREEGLUT_STD_H__
		glutFullScreenToggle();
		#else
		if(
			glutGet(GLUT_WINDOW_WIDTH) == glutGet(GLUT_SCREEN_WIDTH) &&
			glutGet(GLUT_WINDOW_HEIGHT) == glutGet(GLUT_SCREEN_HEIGHT) &&
			glutGet(GLUT_WINDOW_X) == 0 &&
			glutGet(GLUT_WINDOW_Y) == 0
		) {
			glutReshapeWindow(oldwidth,oldheight);
		} else {
			glutFullScreen();
		}
		#endif
	}
	if(key == 'q') {
		#ifdef __FREEGLUT_STD_H__
		glutLeaveMainLoop();
		#else
		#endif
	}
	if(key == '+') {
		steps *= STEP;
	}
	if(key == '-') {
		steps /= STEP;
		if(steps <= 1) steps = 1;
	}
	if(key == '\x1e') {
		// glutLeaveFullScreen();
	}
}
void reshape (int w, int h) {
	oldwidth = width;
	oldheight = height;
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void step() {
	int j,k;
	Colour red = {1.0,0.0,0.0,1.0};
	glutTimerFunc(TIMERMSECS, step, 0);

	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
	glLoadIdentity();

	for(k = 0; k<(int)steps; k++) {
		for(j = 0; j<bodies; ++j) {
			b[j].acceleration = move(&(b[j]),b,bodies,j);
		}
		for(j = 0; j<bodies; ++j) {
			b[j].velocity = vplus(&(b[j].velocity),&(b[j].acceleration));
			b[j].position = vplus(&(b[j].position),&(b[j].velocity));
			b[j].path.pos++;
			PATH_MOD(b[j].path.pos);
			b[j].path.point[b[j].path.pos] = b[j].position;
		}
	}
	for(j = 0; j<bodies; ++j) {
		if(collide(&(b[j]),b,bodies,j)) b[j].colour = red;
		circle(&(b[j].position),sqrt(b[j].mass),&(b[j].colour));
		traverse(&(b[j]),startPath,drawPath,endPath);
	}
	glutSwapBuffers();
}