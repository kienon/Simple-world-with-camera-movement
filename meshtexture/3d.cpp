

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\freeglut.h>
#include <math.h>

#define WIN_WIDTH	800
#define WIN_HEIGHT	800

#define PI 3.141592653
#define DEG_2_RAD (2*PI/360.0)

float angle = 0.0;
// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();
void square();
void cube();
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// camera
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1, 0.0001, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 2.5, 4, 0, 0, 0, 0, 1, 0);

	// lights
	glEnable(GL_LIGHTING);
	GLfloat dir[] = { 1.5,0.5,1.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// depth
	glEnable(GL_DEPTH_TEST);
}

void square(){
	glBegin(GL_QUADS);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glEnd();
}

void cube(){

	glNormal3f(0,0,1);

	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glRotated(0.0, 0,1,0);
		glTranslated(0.0,0.0,1.0);
		square();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glRotated(90.0, 0,1,0);
		glTranslated(0.0,0.0,1.0);
		square();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0, 1.0, 1.0);
		glRotated(180.0, 0,1,0);
		glTranslated(0.0,0.0,1.0);
		square();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glRotated(270.0, 0,1,0);
		glTranslated(0.0,0.0,1.0);
		square();
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0, 0.0, 1.0);
		glRotated(90.0, 1,0,0);
		glTranslated(0.0,0.0,1.0);
		square();
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0, 0.0, 1.0);
		glRotated(-90.0, 1,0,0);
		glTranslated(0.0,0.0,1.0);
		square();
	glPopMatrix();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	
		cube();

	glutSwapBuffers();
	glFlush();

}


// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y -= 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y += 5;

	else if (key == GLUT_KEY_UP)
		rotate_x -= 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x += 5;

	//  Request display update
	glutPostRedisplay();

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("TEST");
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);


	initGL();

	glutMainLoop();

}



