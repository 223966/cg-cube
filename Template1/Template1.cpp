// Template1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"

const double TRIANGLE_LENGTH = 50.0f;
const double OFFSET = TRIANGLE_LENGTH * 2;
const enum Color { red, green, blue, yellow };

double angle = 0.0;

void timer(int) {
	angle += 0.10;
	glutPostRedisplay();
}

void draw() {
	glBegin(GL_POLYGON);
	glVertex2f(-TRIANGLE_LENGTH, -TRIANGLE_LENGTH);
	glVertex2f(TRIANGLE_LENGTH, -TRIANGLE_LENGTH);
	glVertex2f(TRIANGLE_LENGTH, TRIANGLE_LENGTH);
	glEnd();
}

void drawRed() {
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
	draw();
}

void drawGreen() {
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green;
	draw();
}

void drawBlue() {
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue;
	draw();
}

void drawYellow() {
	glColor4f(240.0f, 255.0f, 0.0f, 1.0f);//Yellow;
	draw();
}


void drawTriangle(Color color) {
	switch (color) {
	case red: drawRed(); break;
	case green: drawGreen(); break;
	case blue: drawBlue(); break;
	case yellow: drawYellow(); break;
	}
}

void rotateAroundCenterOfMass() {
	glTranslated(TRIANGLE_LENGTH / 3, -TRIANGLE_LENGTH / 3, 0);
	glRotated(angle, 0, 0, 1);
	glTranslated(-TRIANGLE_LENGTH / 3, TRIANGLE_LENGTH / 3, 0);
}

void drawQuarter(Color color, bool shouldRotate) {
	glPushMatrix();
	if (shouldRotate) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(-OFFSET, 0, 0);
	glPushMatrix();
	if (shouldRotate) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(-OFFSET, 0, 0);
	glPushMatrix();
	if (shouldRotate) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(OFFSET, OFFSET, 0);
	glPushMatrix();
	if (shouldRotate) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(OFFSET, 0, 0);
	glPushMatrix();
	if (shouldRotate) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(0, OFFSET, 0);
	glPushMatrix();
	if (shouldRotate) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
}

void drawFigure() {
	drawQuarter(red, true);
}

void MyDisplay(void) {
	// The new scene
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glLoadIdentity();


	drawFigure();

	// The end of scene
	glFlush();//start processing buffered OpenGL routines

	glutTimerFunc(0.1, timer, 0);

}
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
									 /* initialize viewing values */
	glViewport(0, 0, 300, 300);//window origin and size
	glMatrixMode(GL_PROJECTION);//
	glLoadIdentity();//=1
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//=1
}

int main(int argc, char** argv) { //<- for normal API
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//single buffer and RGBA
	glutInitWindowSize(500, 500);//initial window size
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Triangles Excercise");//create widnow, hello title bar
	MyInit();
	glutDisplayFunc(MyDisplay);//
	glutMainLoop();//enter main loop and process events
	return 0;
}