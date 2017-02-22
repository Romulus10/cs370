#include <GL/glut.h>
#include <math.h>

void transform_eye() {
    int *y_rot = {
        {},
        {},
        {},
        {}
    };

}

void draw_triangles() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(0.5,0.0,0.0);
    glEnd();
    glFlush();
}

void init_mod() {

}

void display(void) {

    transform_eye();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 40.0, 1.0, 1.0, 10000.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 5.0, 5.0, 5.0,
	           0.0, 0.0, 0.0,
	           0.0, 1.0, 0.0
               );

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw_triangles();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutIdleFunc(glutPostRedisplay);
	glEnable(GL_DEPTH_TEST);
	init_mod();
	glutMainLoop();
}
