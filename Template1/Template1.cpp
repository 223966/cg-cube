// Template1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"

// You can change these parameters
const double TRIANGLE_LENGTH = 100.0f;
const double SPREAD_STEP = 0.10;
const double SPREAD_LIMIT = 150.0;

const bool shouldRotateAroundCenterOfMass = true;
const bool shouldRotateAroundOrigin = false;
const bool shouldSpread = true;

// ******************************* //

const double OFFSET = TRIANGLE_LENGTH;

const enum Color { red, green, blue, yellow };

double angle = 0.0;
double spread = 0.0;
bool shouldIncrease = true;

void timer(int) {
	angle += 180 / SPREAD_LIMIT * SPREAD_STEP;
	spread += shouldIncrease ? SPREAD_STEP : -SPREAD_STEP;
	if (spread >= SPREAD_LIMIT) shouldIncrease = false;
	if (spread <= 00.0) shouldIncrease = true;
	glutPostRedisplay();
}

void draw() {
	glBegin(GL_POLYGON);
	glVertex2f(-TRIANGLE_LENGTH, 0);
	glVertex2f(0, 0);
	glVertex2f(0, TRIANGLE_LENGTH);
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
	glTranslated(-TRIANGLE_LENGTH / 3, TRIANGLE_LENGTH / 3, 0);
	glRotated(angle, 0, 0, 1);
	glTranslated(TRIANGLE_LENGTH / 3, -TRIANGLE_LENGTH / 3, 0);
}

void spreadOut() {
	glTranslated(-spread, spread, 0);
}

void drawQuarter(Color color) {
	glPushMatrix();
	if (shouldSpread) spreadOut();
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(-OFFSET, 0, 0);
	glPushMatrix();
	if (shouldSpread) spreadOut();
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(-OFFSET, 0, 0);
	glPushMatrix();
	if (shouldSpread) spreadOut();
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(OFFSET, OFFSET, 0);
	glPushMatrix();
	if (shouldSpread) spreadOut();
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(OFFSET, 0, 0);
	glPushMatrix();
	if (shouldSpread) spreadOut();
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
	glTranslated(0, OFFSET, 0);
	glPushMatrix();
	if (shouldSpread) spreadOut();
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass();
	drawTriangle(color);
	glPopMatrix();
}

void drawFigure() {
	glPushMatrix();
	drawQuarter(red);
	glPopMatrix();
	glRotated(180, 0, 1, 0);
	glPushMatrix();
	drawQuarter(green);
	glPopMatrix();
	glRotated(180, 1, 0, 0);
	glPushMatrix();
	drawQuarter(yellow);
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

	glutTimerFunc(0.01, timer, 0);

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