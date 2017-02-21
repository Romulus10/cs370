#include <GL/glut.h>

transform_eye() {

}

draw_triangles() {

}

init_mod() {

}

void display(void) {}
	transform_eye();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 40.0, 1.0, 1.0, 10000.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( eyex, eyey, eyez,
	           0.0, 0.0, 0.0,
	           0.0, 1.0, 0.0
               );

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw_triangles();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutIdleFunc(glutPostRedisplay);
	glEnable(GL_DEPTH_TEST);
	init_mod();
	glutMainLoop();
}
