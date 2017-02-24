#include <GL/glut.h>
#include <math.h>
#include "../lib/matrix.h"

double *eye;

double *transform_eye(double *eye) {
    double y_rot[4][4] = {
        {cos(1.0), 0.0, sin(1.0), 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {-sin(1.0), 0.0, cos(1.0), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return multiply(*y_rot, eye);
}

void draw_triangles() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
    glEnd();
    glFlush();
}

void display(void) {

    eye = transform_eye(eye);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 40.0, 1.0, 1.0, 10000.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( eye[0], eye[1], eye[2],
	           0.0, 0.0, 0.0,
	           0.0, 1.0, 0.0
               );

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw_triangles();

	glutSwapBuffers();
}

int main(int argc, char** argv) {

    eye = malloc(sizeof(double) * 4);

    eye[0] = 5.0;
    eye[1] = 5.0;
    eye[2] = 5.0;
    eye[3] = 1.0;

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutIdleFunc(glutPostRedisplay);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
