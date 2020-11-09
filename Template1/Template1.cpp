#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"

#define WIDTH 640
#define HEIGHT 480

const float RED[3] = { 1.0f, 0.0f, 0.0f };
const float GREEN[3] = { 0.0f, 1.0f, 0.0f };
const float BLUE[3] = { 0.0f, 0.0f, 1.0f };
const float MAGENTA[3] = { 255.0f, 0.0f, 255.0f };
const float YELLOW[3] = { 255.0f, 255.0f, 0.0f };


float ver[8][3] =
{
    {-1.0,-1.0,1.0},
    {-1.0,1.0,1.0},
    {1.0,1.0,1.0},
    {1.0,-1.0,1.0},
    {-1.0,-1.0,-1.0},
    {-1.0,1.0,-1.0},
    {1.0,1.0,-1.0},
    {1.0,-1.0,-1.0},
};

void drawQuad(const float color[3], int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color);
    glVertex3fv(ver[a]);
    glVertex3fv(ver[b]);
    glVertex3fv(ver[c]);
    glVertex3fv(ver[d]);
    glEnd();
}

void drawCube() {
    drawQuad(GREEN, 2, 3, 7, 6);
    drawQuad(RED, 2, 6, 5, 1);
    drawQuad(BLUE, 2, 1, 0, 3);
    drawQuad(MAGENTA, 4, 5, 1, 0);
    drawQuad(YELLOW, 7, 4, 0, 3);
    drawQuad(BLUE, 7, 6, 5, 4);
}

double rotate_y = 0;
double rotate_x = 0;
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        rotate_x += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_x -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_y += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_y -= 5;
    glutPostRedisplay();
}

void drawCoordinates() {
    // x red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);
    glEnd();

    // y green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);
    glEnd();

    // z blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f, -4.0f);
    glVertex3f(0.0, 0.0f, 4.0f);
    glEnd();

}

void MyDisplay()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, WIDTH / HEIGHT, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
       5, 5, 5,
        0, 0, 0,
        0, 0, 1
    );

    glRotated(rotate_x, 1.0, 0.0, 0.0);
    glRotated(rotate_y, 0.0, 1.0, 0.0);
    //drawCoordinates();
    drawCube();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("GLUT");
    glutDisplayFunc(MyDisplay);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

