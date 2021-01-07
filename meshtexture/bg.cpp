#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\freeglut.h>
#include "Vector3D.h"
#include "Point3D.h"
#include "texture.h"
#include "mesh.h"
#include "texturedSquare.h"
#include "camera.h"


#define screenWidth		500
#define screenHeight	500
#define FPS				30
#define PI				3.14159265

Mesh mesh;
TexturedSquare square;
TexturedSquare square1;
TexturedSquare square2;
TexturedSquare square3;
TexturedSquare square4;
TexturedSquare square5;
Camera cam;

//Background back;
double rot;

/*void bgsquare()
{
	glBegin(GL_QUADS);
	glVertex3f(5, 5, -3);
	glVertex3f(-5, 5, -3);
	glVertex3f(-5, -5, -3);
	glVertex3f(5, -5, -3);
	glEnd();
}*/


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();



	glTranslated(0.0, 1.0, 0.0);
	glRotated(0.0, 0.0, 0.0, 0.0);
	glScaled(4.5, 4.5, 4.5);
	square.draw(); //the square base
	glPopMatrix();

	glPushMatrix();

	glTranslated(0.0, 1.5, 0.0);
	glRotated(0.0, 0.0, 0.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	mesh.Draw(); //the square box
	glPopMatrix();

	glPushMatrix();

	glTranslated(-5.0, 1.5, 0.0);
	glRotated(0.0, 0.0, 0.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	mesh.Draw(); //the square box
	glPopMatrix();




	glFlush();
	glutSwapBuffers();
}

void idle() {
	DWORD start = GetTickCount();

	while (GetTickCount() - start < 1000 / FPS);

	rot += (PI / 2.0);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

	cam.Update(key);


}

void initGL() {

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	GLfloat lightpos[] = { 2.0, 3.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1, 1000.0);
	//gluLookAt(3.5,3.0,3.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	cam.Set(Point3D(0.0, 1, 5.0), Point3D(0.0, 0.0, 0.0), Vector3D(0.0, 1.0, 0.0));
}

void init() {
	Textures_Initialise();
	mesh.Load((char*)"box.txt");
	square.set(2.0, (char*)"base.bmp");
	square1.set(2.0, (char*)"base.bmp");
	square2.set(2.0, (char*)"grass.bmp");
	square3.set(2.0, (char*)"base.bmp");
	square4.set(2.0, (char*)"base.bmp");
	square5.set(2.0, (char*)"base.bmp");

	mesh.Load((char*)"pyramid.txt");

}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInit(&argc, argv);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Test");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	init();
	initGL();

	glutMainLoop();
}