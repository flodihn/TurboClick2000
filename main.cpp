#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glu.h>
#include <GL/freeglut.h>

typedef struct State {
	int windowWidth = 800;
	int windowHeight = 600;
	int clicks;
	float clicksPerSec;
	float rot;
	GLfloat normalColor[3];
	GLfloat c1[3];
	GLfloat c2[3];
	GLfloat c3[3];
	GLfloat c4[3];
} State;

State state;

void initState()
{
	state.clicks = 1;
	state.rot = 0.0f;
	state.clicksPerSec = 0.0f;
	state.normalColor[0] = 0.5f, state.normalColor[1] = 0.5f; state.normalColor[2] = 0.5f;
	state.c1[0] = 1.0f, state.c1[1] = 0.0f; state.c1[2] = 0.0f;
	state.c2[0] = 0.0f, state.c2[1] = 0.0f; state.c2[2] = 0.0f;
	state.c3[0] = 0.0f, state.c3[1] = 0.0f; state.c3[2] = 0.0f;
}

void onKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '\x1B':
		{
			exit(EXIT_SUCCESS);
			break;
		}
	}
}

void onMouseButton(int mbutton, int mstate, int x, int y)
{
	if(mbutton == GLUT_LEFT_BUTTON && mstate == GLUT_DOWN) {
		state.clicks += 1;
		//state.c1[0] = 1.0f;
		//state.c1[1] = 1.0f;
		//state.c1[3] = 1.0f;
	}
}

void idle()
{
	state.rot += 0.001f;
	
}

void windowReshape(int width, int height)
{
	if (height==0)
	{
		height=1;
	}

	state.windowHeight = width;
	state.windowHeight = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                           // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
	//glOrtho(0.0f, state.windowWidth, 0.0f, state.windowHeight, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
	glLoadIdentity();                           // Reset The Modelview Matrix
}

void drawPyramid()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, -5.0f);
	glRotatef(state.rot, 0.0f, 1.0f, 0.0f); 
	glBegin(GL_TRIANGLES);
	glColor3f(state.c1[0], state.c1[1], state.c1[2]); glVertex3f(0.0f, 1.0f, 0.0f );
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f );
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.5f, 0.0f, -0.5f);

	glColor3f(state.c1[0], state.c1[1], state.c1[2]); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.7f);

	glColor3f(state.c1[0], state.c1[1], state.c1[2]); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.7f);
	glEnd();

	glPopMatrix();
}

void drawText()
{
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPushMatrix();
	glOrtho(0.0f, state.windowWidth, -state.windowHeight, 0.0f, 0.0f, 1.0f);
	unsigned char text[] = "Foobar.";
	int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, text);
	float x = .5; /* Centre in the middle of the window */
	glRasterPos2f(x - (float) state.windowWidth / 2, 0.);
	int len = 7;
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	}
	glPopMatrix();
	/*
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glTranslatef(0.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(10, state.windowWidth - 10);  // move in 10 pixels from the left and bottom edges
	char text[] = "foobar";
	for (int i = 0; i < 6; ++i )
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[i]);
	}
	glPopMatrix();
	*/
}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	drawPyramid();
	//drawText();

	//glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -1.0f, 1.0f);
	//glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	//glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);


	glutSwapBuffers();
}

int initGL()
{
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return 1;
}

void initGLUT(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(state.windowWidth, state.windowHeight);
	glutCreateWindow("TURBO CLICK 2000");
	glutReshapeFunc(&windowReshape);
	glutKeyboardFunc(&onKeyboard);
	glutMouseFunc(&onMouseButton);
	glutDisplayFunc(&display);
}

int main(int argc, char **argv) {
	initState();
	initGLUT(argc, argv);
	initGL();

	for(;;)
	{
		state.rot += 0.01 * state.clicks;
		glutMainLoopEvent();
		glutPostRedisplay();
		usleep(1000); // sleep 1 ms
	}
	glutMainLoop();
	return 1;
}