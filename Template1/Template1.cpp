// Template1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"

// You can change these parameters
const double TRIANGLE_LENGTH = 80.0f;
const double SPREAD_STEP = 1;
const double SPREAD_LIMIT = 125.0;

const bool shouldRotateAroundCenterOfMass = true;
const bool shouldRotateAroundOrigin = true;
const bool shouldSpread = true;

// ******************************* //

const double OFFSET = TRIANGLE_LENGTH * 1.5;

const enum Color { red, green, blue, yellow };
const enum Direction {left, right};
const enum Position {bottomOuter, bottomInner, center, topInner, topOuter};

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

void rotateAroundOrigin(Direction direction) {
	switch (direction) {
	case left: 	glRotated(angle, 0, 0, 1); break;
	case right: glRotated(-angle, 0, 0, 1); break;
	}
}

void rotateAroundCenterOfMass(Direction direction) {
	if (direction == left) {
		glTranslated(-TRIANGLE_LENGTH / 3, TRIANGLE_LENGTH / 3, 0);
		glRotated(angle, 0, 0, 1);
		glTranslated(TRIANGLE_LENGTH / 3, -TRIANGLE_LENGTH / 3, 0);
	}
	else {
		glTranslated(-TRIANGLE_LENGTH / 3, TRIANGLE_LENGTH / 3, 0);
		glRotated(-angle, 0, 0, 1);
		glTranslated(TRIANGLE_LENGTH / 3, -TRIANGLE_LENGTH / 3, 0);
	}
	
}

void spreadOut(Position position) {
	if(position == center) glTranslated(-spread, spread, 0);
	if(position == bottomInner) glTranslated(-spread, spread * 0.75, 0);
	if(position == bottomOuter) glTranslated(-spread, spread * 0.5, 0);
	if(position == topInner) glTranslated(-spread * 0.75, spread, 0);
	if(position == topOuter) glTranslated(-spread * 0.5, spread, 0);
}

void drawQuarter(Color color) {
	glPushMatrix();
	if (shouldRotateAroundOrigin) rotateAroundOrigin(left);
	if (shouldSpread) spreadOut(center);
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass(left);
	drawTriangle(color);
	glPopMatrix();
	glTranslated(-OFFSET, 0, 0);
	glPushMatrix();
	if (shouldRotateAroundOrigin) {
		glTranslated(OFFSET, 0, 0);
		rotateAroundOrigin(right);
		glTranslated(-OFFSET, 0, 0);
	} 
	if (shouldSpread) spreadOut(bottomInner);
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass(right);
	drawTriangle(color);
	glPopMatrix();
	glTranslated(-OFFSET, 0, 0);
	glPushMatrix();
	if (shouldRotateAroundOrigin) {
		glTranslated(OFFSET*2, 0, 0);
		rotateAroundOrigin(left);
		glTranslated(-OFFSET*2, 0, 0);
	}
	if (shouldSpread) spreadOut(bottomOuter);
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass(left);
	drawTriangle(color);
	glPopMatrix();
	glTranslated(OFFSET, OFFSET, 0);
	glPushMatrix();
	if (shouldRotateAroundOrigin) {
		glTranslated(OFFSET, -OFFSET, 0);
		rotateAroundOrigin(left);
		glTranslated(-OFFSET, OFFSET, 0);
	}
	if (shouldSpread) spreadOut(center);
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass(left);
	drawTriangle(color);
	glPopMatrix();
	glTranslated(OFFSET, 0, 0);
	glPushMatrix();
	if (shouldRotateAroundOrigin) {
		glTranslated(0, -OFFSET, 0);
		rotateAroundOrigin(right);
		glTranslated(0, OFFSET, 0);
	}
	if (shouldSpread) spreadOut(topInner);
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass(right);
	drawTriangle(color);
	glPopMatrix();
	glTranslated(0, OFFSET, 0);
	glPushMatrix();
	if (shouldRotateAroundOrigin) {
		glTranslated(0, -OFFSET*2, 0);
		rotateAroundOrigin(left);
		glTranslated(0, OFFSET*2, 0);
	}
	if (shouldSpread) spreadOut(topOuter);
	if (shouldRotateAroundCenterOfMass) rotateAroundCenterOfMass(left);
	drawTriangle(color);
	glPopMatrix();
}

void drawFigure() {
	glPushMatrix();
	glRotated(0, 0, 0, 0);
	drawQuarter(red);
	glPopMatrix();
	glPushMatrix();
	glRotated(180, 0, 0, 1);
	drawQuarter(green);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawQuarter(yellow);
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 0, 0, 1);
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