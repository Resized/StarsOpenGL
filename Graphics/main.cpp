#include "glut.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int MAX_STARS = 1000;
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1200;
const double MIN_STAR_SIZE = 2.0;
const double SPEED = 1.005;

typedef struct {
	double x,y,r,g,b;
} POINT_2D;

POINT_2D starsArr[MAX_STARS];

void init()
{
	glOrtho(-1, 1, -1, 1, -1, 1);
	glClearColor(0,0,0.1,0);// color of window background
	
	srand(time(NULL));
	for (int i = 0; i < MAX_STARS; i++)
	{
		starsArr[i].x = (rand() % 1000) / 500.0 - 1; // random number in (-1,1)
		starsArr[i].y = (rand() % 1000) / 500.0 - 1; // random number in (-1,1)
		starsArr[i].r = (rand() % 1000) / 1000.0;
		starsArr[i].g = (rand() % 1000) / 1000.0;
		starsArr[i].b = (rand() % 1000) / 1000.0;
	}
}

void displayStars()
{
	//glPointSize(1);
	for (int i = 0; i < MAX_STARS; i++)
	{
		glPointSize(1 + MIN_STAR_SIZE * (fabs(starsArr[i].x) + fabs(starsArr[i].y)));
		glBegin(GL_POINTS);
		glColor3d(starsArr[i].r, starsArr[i].g, starsArr[i].b);
		glVertex2d(starsArr[i].x, starsArr[i].y);
		glEnd();
	}
}

void checkOutbounds(POINT_2D* star) // Check if star
{
	if (fabs(star->x) > 1)
		star->x = ((rand() % 1000) / 500.0 - 1) / 4.0;
	if (fabs(star->y) > 1)
		star->y = ((rand() % 1000) / 500.0 - 1) / 4.0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	displayStars();

	glutSwapBuffers(); // show all
}

void idle() 
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		starsArr[i].x *= SPEED;
		starsArr[i].y *= SPEED;
		checkOutbounds(&starsArr[i]);
	}

	glutPostRedisplay();
}


void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("First Example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();

	glutMainLoop();
}