#include "glut.h"
#include "gl/GLU.h"
#include "gl/pch.h"
#include <iostream>
#include <windows.h>

using namespace std;

int width = 720;
int height = 720;

GLfloat rx = 0;
GLfloat ry = 0;
GLfloat tx = 0;
GLfloat ty = 0;
GLfloat tz = -9;
GLint tt = 0;

void Mouse(int button, int state, int x, int y);
void MouseMotion(int x, int y);

GLuint list = 0;
int mx, my;
bool ldown = false;
bool rdown = false;
GLboolean bTimer = 0;
GLuint OldTick;
GLuint FramesCount;
GLuint StartTick;

void Init() {
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = width / height;
	gluPerspective(120.0f, 1, 0.1f, -100);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	GLfloat fSpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecularLight);
	GLfloat fLightPosition[] = { -10.0f, 10.0f, 20.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosition);
	glEnable(GL_LIGHT0);

	GLfloat fMaterial[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, fMaterial);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fSpecularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);


	glColor3f(0, 0, 1);
	glClearColor(0.2f, 0.0f, 0.2f, 0);	
	
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glTranslatef(0, 0, 0);
	glutSolidTeapot(1.0f);

	glEndList();
	glFlush();

}

void Timer(int val) {

	if (bTimer) {
		ry += 2;
		glutPostRedisplay();
		glutTimerFunc(25, Timer, 1);
	}
	else
	{
		glutMouseFunc(Mouse);
		glutMotionFunc(MouseMotion);
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glRotatef(rx, 1, 0, 0);
	glRotatef(ry, 0, 1, 0);
	glCallList(list);
	glPopMatrix();
	glutSwapBuffers();
}

void Keybord(unsigned char key, int x, int y) {
	switch (key)
	{
	case VK_ESCAPE:
		if (list)
			glDeleteLists(list, 1);
		exit(0);
		break;

	case '+':
		tz += 0.2;
		Display();
		break;

	case '-':
		tz -= 0.2;
		Display();
		break;

	case 'a':
		tx -= 0.2;
		Display();
		break;

	case 'd':
		tx += 0.2;
		Display();
		break;

	case 's':
		ty -= 0.2;
		Display();
		break;

	case 'w':
		ty += 0.2;
		Display();
		break;

	case 'r' | 'R':
		bTimer = !bTimer;
		if (bTimer) {
			glutTimerFunc(25, Timer, 1);
			glutMouseFunc(NULL);
			glutMotionFunc(NULL);
		}
		break;
	}
}

void Reshape(int aWidth, int aHeight) {
	glViewport(0, 0, aWidth, aHeight);
	width = aWidth;
	height = aHeight;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, GLdouble(width) / height, 1, 100);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:
			ldown = true;
			mx = x;
			my = y;
			break;

		case GLUT_UP:
			ldown = false;
			break;
		}
	}

	if (button == GLUT_RIGHT_BUTTON) {
		switch (state)
		{
		case GLUT_DOWN:
			rdown = true;
			mx = x;
			my = y;
			break;

		case GLUT_UP:
			rdown = false;
			break;
		}
	}
}

void MouseMotion(int x, int y) {
	if (ldown) {
		rx += 0.5 * (y - my);
		ry += 0.5 * (x - mx);
		mx = x;
		my = y;
		glutPostRedisplay();
	}

	if (rdown) {
		tx += 0.1 * (x - mx);
		if (tt)
			tz += 0.01 * (y - my);
		else
			ty += 0.01 * (my - y);
		mx = x;
		my = y;
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("6");
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keybord);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutMainLoop();
	return 0;
}