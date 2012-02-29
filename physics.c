#include "physics.h"

int bodyTotal;
Body *bodyArray;
double steps = 2.0;
double speed = 0.01;
Vector heading, left, up, cpos, target;
double ctheta, stheta;


void timerFunc(int notUsed) {
	Vector temp = smult (speed, &heading);
	cpos = vplus (&cpos, &temp);
	target = vplus (&cpos, &temp);
	glutPostRedisplay ();
}

void reshape (int width, int height) {

	if (height == 0) height = 1;
	glViewport (0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 100.0f);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {

	switch (key) {
		case 27:
			exit(0);
			break;
		case 'W':
		case 'w':
			speed += 0.02;
			break;
		case 'S':
		case 's':
			speed -= 0.02;
			if (speed < 0.02) speed = 0.0000000001; 
			break;
		case 'R':
		case 'r':
			steps = 2.0;
			speed = 0.01;
			initialiseArray ();
		case 'V':
		case 'v':
			heading = newVector (0, 0, -1);
			left = newVector (-1, 0, 0);
			up = newVector (0, 1, 0);
			cpos = newVector (0, 0, 10);
			target = vplus (&cpos, &heading);
			break;
		case '+':
			steps *= STEP;
			break;
		case '-':
			steps /= STEP;
			if(steps < 1) steps = 1;
			break;
		case ',': {
			Vector temp, temp1, temp2;
			temp1 = smult (ctheta, &heading);
			temp2 = smult (stheta, &left);
			temp = vplus (&temp1, &temp2);
			temp1 = smult (stheta, &heading);
			temp2 = smult (ctheta, &left);
			left = vminus (&temp2, &temp1);
			heading = temp;
			target = vplus (&cpos, &heading);
			break;
		}
		case '.': {
			Vector temp, temp1, temp2;
			temp1 = smult (ctheta, &heading);
			temp2 = smult (stheta, &left);
			temp = vminus (&temp1, &temp2);
			temp1 = smult (stheta, &heading);
			temp2 = smult (ctheta, &left);
			left = vplus (&temp1, &temp2);
			heading = temp;
			target = vplus (&cpos, &heading);
			break;
		}
		default:
			break;
	}
}

void special (int key, int x, int y) {
	
	switch (key) {
		Vector temp, temp1, temp2;
		case GLUT_KEY_UP:
			temp1 = smult (ctheta, &heading);
			temp2 = smult (stheta, &up);
			temp = vminus (&temp1, &temp2);
			temp1 = smult (stheta, &heading);
			temp2 = smult (ctheta, &up);
			up = vplus (&temp1, &temp2);
			heading = temp;
			target = vplus (&cpos, &heading);
			break;
		case GLUT_KEY_DOWN:
			temp1 = smult (ctheta, &heading);
			temp2 = smult (stheta, &up);
			temp = vplus (&temp1, &temp2);
			temp1 = smult (stheta, &heading);
			temp2 = smult (ctheta, &up);
			up = vminus (&temp2, &temp1);
			heading = temp;
			target = vplus (&cpos, &heading);
			break;
		case GLUT_KEY_LEFT:
			temp1 = smult (ctheta, &left);
			temp2 = smult (stheta, &up);
			temp = vminus (&temp1, &temp2);
			temp1 = smult (stheta, &left);
			temp2 = smult (ctheta, &up);
			up = vplus (&temp1, &temp2);
			left = temp;
			break;
		case GLUT_KEY_RIGHT:
			temp1 = smult (ctheta, &left);
			temp2 = smult (stheta, &up);
			temp = vplus (&temp1, &temp2);
			temp1 = smult (stheta, &left);
			temp2 = smult (ctheta, &up);
			up = vminus (&temp2, &temp1);
			left = temp;
			break;
		case GLUT_KEY_PAGE_UP:
			cpos = target;
			target = vplus (&cpos, &heading);
			break;
		case GLUT_KEY_PAGE_DOWN:
			target = cpos;
			cpos = vminus (&target, &heading);
			break;
		default:
			return;
	}
}

void display (void) {

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	gluLookAt (cpos.x, cpos.y, cpos.z, target.x, target.y, target.z, up.x, up.y, up.z);
	int k;
	Body *bp;
	Body *bBegin;
	Body *bEnd;
	glutTimerFunc (TIMERMSECS, timerFunc, 0);
	bBegin = bodyArray;
	bEnd = bodyArray + bodyTotal;
	for (k = 0; k < (int)steps; ++k) {
		for (bp = bBegin; bp != bEnd; ++bp) {
			bp->acceleration = move (bp, bodyArray, bodyTotal);
		}
		for (bp = bBegin; bp != bEnd; ++bp) {
			bp->velocity = vplus (&(bp->velocity), &(bp->acceleration));
			bp->position = vplus (&(bp->position), &(bp->velocity));
			bp->path.pos++;
			PATH_MOD (bp->path.pos);
			bp->path.point[bp->path.pos] = bp->position;
		}
	}
	for (bp = bBegin; bp != bEnd; ++bp) {
		drawBody (&(bp->position), sqrt (bp->mass), &(bp->colour));
		drawPath (bp);
	}
	glutSwapBuffers ();
}

void drawBody (Vector *pos, double r, Vector *c) {

	r /= 100;
	glPushMatrix ();
	glTranslated (pos->x, pos->y, pos->z);
	glScaled (r, r, r);
	glColor3dv ((double *)c);
	glCallList (1);
	glPopMatrix ();
}

void drawPath (Body *b) {

	int i, j;
	glBegin (GL_LINE_STRIP);
	for (i = 1; i < PATHLEN; ++i) {
		j = i + b->path.pos;
		PATH_MOD (j);
		glColor4f (b->colour.x, b->colour.y, b->colour.z, (double)i / (double)PATHLEN);
		glVertex3f (b->path.point[j].x, b->path.point[j].y, b->path.point[j].z);
	}
	glEnd (); 
}

void initialiseSettings (void) {

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable (GL_DEPTH_TEST);
	glBlendFunc (GL_SRC_ALPHA, GL_ZERO);
	glEnable (GL_BLEND);
	glCullFace (GL_BACK);
	glEnable (GL_CULL_FACE);
	glNewList (1, GL_COMPILE);
	glutSolidSphere (1, 10, 10);
	glEndList ();
	heading = newVector (0, 0, -1);
	left = newVector (-1, 0, 0);
	up = newVector (0, 1, 0);
	cpos = newVector (0, 0, 10);
	target = vplus (&cpos, &heading);
	ctheta = cos (TURN_ANGLE);
	stheta = sin (TURN_ANGLE);
}

void initialiseArray (void) {

	int i;
	double posrep = 2.0 / RAND_MAX;
	double velrep = 0.004 / RAND_MAX;
	for (i = 0; i < bodyTotal; ++i) {
		bodyArray[i] = newBody (
			newVector (
				1.0 - posrep * rand (),
				1.0 - posrep * rand (),
				1.0 - posrep * rand ()
			),
			newVector (
				0.002 - velrep * rand (),
				0.002 - velrep * rand (),
				0.002 - velrep * rand ()
			),
			100.0 * rand() / RAND_MAX
		);
	}
}

int main (int argc, char **argv) {

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (INIT_WIN_WIDTH, INIT_WIN_HEIGHT);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Physics Fork");
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);
	if(argc != 2) {
		printf("Usage: %s numbodies; Continuing with 100\n",argv[0]);
		bodyTotal = 100;
	}
	else bodyTotal = atoi(argv[1]);
	bodyArray = malloc (bodyTotal * sizeof (Body));
	initialiseArray ();
 	initialiseSettings ();
	glutMainLoop ();
	return 0;
}
