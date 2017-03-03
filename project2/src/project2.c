#include <GL/glut.h>
#include <math.h>

double *eye;

double *transform_eye() {
    // Simplified algorithm for a full y-transform
    // Adapted from:
    // https://open.gl/transformations
    eye[0] = ((cos(1 * (M_PI/180)) * eye[0]) + (sin(1 * (M_PI/180)) * eye[2]));
    eye[1] = eye[1];
    eye[2] = ((-sin(1 * (M_PI/180)) * eye[0]) + (cos(1 * (M_PI/180)) * eye[2]));
    eye[3] = 1;
}

void draw_triangles() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    static const double triangles[] = {
        -0.5,-0.5,-0.5,
        -0.5,-0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5,-0.5,
        0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        0.5,-0.5, 0.5,
        -0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5,-0.5, 0.5,
        0.5,-0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5,-0.5,
        -0.5, 0.5,-0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5,-0.5, 0.5
    };

    int i;
    for (i = 0; i < 42; i = i + 3) {
        glVertex3f(triangles[i], triangles[i+1], triangles[i+2]);
    }

    glEnd();
    glFlush();
}

void display(void) {

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

    transform_eye();

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
