#include "glut.h"
#include "gl/GLU.h"

#define APPLICATION_TITLE "ex5. OpenGL 3D Models"
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(-3, -3, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireTorus(0.25, 0.5, 30, 30);

	glTranslatef(2, 2, 0);
	glColor3f(0.0f, 1.0f, 1.0f);
	glutSolidDodecahedron();

	glTranslatef(2, 2, 0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCone(0.5, 1, 30, 30);

	glTranslatef(1.5, 1.5, 0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidTeapot(0.5f);

	glTranslatef(1.5, 1.5, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(0.5f);

	glFlush();
	glutSwapBuffers();
}


void Reshape(int nWidth, int nHeight)
{
	glViewport(0, 0, (GLsizei)nWidth, (GLsizei)nHeight);
}

void InitScene()
{
	glClearColor(0.2f, 0.0f, 0.2f, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat aspect = WINDOW_WIDTH / WINDOW_HEIGHT;

	gluPerspective(110.0f, 1, 0.1f, -100);

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glShadeModel(GL_SMOOTH);
	glShadeModel(GL_FLAT);

	/* Light */
	glEnable(GL_LIGHTING);
	GLfloat fSpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecularLight);
	GLfloat fLightPosition[] = { -10.0f, 10.0f, 20.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosition);

	glEnable(GL_LIGHT0);

	/* Materials */
	GLfloat fMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, fMaterial);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fSpecularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow(APPLICATION_TITLE);

	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(display);

	InitScene();
	glutMainLoop();
}