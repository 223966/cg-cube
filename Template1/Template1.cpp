// Template1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"

const float TRIANGLE_LENGTH = 100.0f;
const float CENTER = 0.0f;
const enum Color { red, green, blue, yellow };


void drawRed() {
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
	glVertex2f(-TRIANGLE_LENGTH, CENTER);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
	glVertex2f(CENTER, CENTER);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
	glVertex2f(CENTER, TRIANGLE_LENGTH);
	glEnd();
}

void drawGreen() {
	glBegin(GL_POLYGON);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green;
	glVertex2f(-TRIANGLE_LENGTH, CENTER);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green;
	glVertex2f(CENTER, CENTER);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green;
	glVertex2f(CENTER, TRIANGLE_LENGTH);
	glEnd();
}

void drawBlue() {
	glBegin(GL_POLYGON);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue;
	glVertex2f(-TRIANGLE_LENGTH, CENTER);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue;
	glVertex2f(CENTER, CENTER);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue;
	glVertex2f(CENTER, TRIANGLE_LENGTH);
	glEnd();
}

void drawYellow() {
	glBegin(GL_POLYGON);
	glColor4f(240.0f, 255.0f, 0.0f, 1.0f);//Yellow;
	glVertex2f(-TRIANGLE_LENGTH, CENTER);
	glColor4f(240.0f, 255.0f, 0.0f, 1.0f);//Yellow;
	glVertex2f(CENTER, CENTER);
	glColor4f(240.0f, 255.0f, 0.0f, 1.0f);//Yellow;
	glVertex2f(CENTER, TRIANGLE_LENGTH);
	glEnd();
}

void drawTriangle(Color color) {
	switch (color) {
	case red: drawRed(); break;
	case green: drawGreen(); break;
	case blue: drawBlue(); break;
	case yellow: drawYellow(); break;
	}
}

void drawQuarter(Color color) {
	drawTriangle(color);
	glTranslated(-TRIANGLE_LENGTH, 0, 0);
	drawTriangle(color);
	glTranslated(-TRIANGLE_LENGTH, 0, 0);
	drawTriangle(color);
	glTranslated(TRIANGLE_LENGTH, TRIANGLE_LENGTH, 0);
	drawTriangle(color);
	glTranslated(TRIANGLE_LENGTH, 0, 0);
	drawTriangle(color);
	glTranslated(0, TRIANGLE_LENGTH, 0);
	drawTriangle(color);
}

void drawFigure() {
	glPushMatrix();
	drawQuarter(red);
	glPopMatrix();
	glRotated(180, 0, 1, 0);
	glPushMatrix();
	drawQuarter(yellow);
	glPopMatrix();
	glRotated(180, 1, 0, 0);
	glPushMatrix();
	drawQuarter(green);
	glPopMatrix();
	glRotated(180, 0, 1, 0);
	glPushMatrix();
	drawQuarter(blue);
	glPopMatrix();
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