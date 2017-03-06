/*
 * Sean Batzel
 *
 * CMPS 370
 * Rotating Cube
 */


#include <GL/glut.h>
#include <math.h>

double *eye;

double *transform_eye() {
    // Simplified algorithm for a full y-transform
    // This takes the full matrix multiplication and
    // reduces it down to a manageable number of steps.
    // ISSUE:
    //  math.h trig functions deal in radians.
    //  degrees = radians * (π / 180)
    //  doubles lose some precision,
    //  leading to the observer straying from
    //  a perfect rotation.
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

    /*
    static const double colors[3][3] = {
        {1.0,0.0,0.0},
        {0.0,1.0,0.0},
        {0.0,0.0,1.0}
    };
    */

    static const double triangles[36][3] = {
        {-0.5,-0.5,-0.5},
        {-0.5,-0.5, 0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5,-0.5},
        {-0.5,-0.5,-0.5},
        {-0.5, 0.5,-0.5},
        {0.5,-0.5, 0.5},
        {-0.5,-0.5,-0.5},
        {0.5,-0.5,-0.5},
        {0.5, 0.5,-0.5},
        {0.5,-0.5,-0.5},
        {-0.5,-0.5,-0.5},
        {-0.5,-0.5,-0.5},
        {-0.5, 0.5, 0.5},
        {-0.5, 0.5,-0.5},
        {0.5,-0.5, 0.5},
        {-0.5,-0.5, 0.5},
        {-0.5,-0.5,-0.5},
        {-0.5, 0.5, 0.5},
        {-0.5,-0.5, 0.5},
        {0.5,-0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5,-0.5,-0.5},
        {0.5, 0.5,-0.5},
        {0.5,-0.5,-0.5},
        {0.5, 0.5, 0.5},
        {0.5,-0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, 0.5,-0.5},
        {-0.5, 0.5,-0.5},
        {0.5, 0.5, 0.5},
        {-0.5, 0.5,-0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {-0.5, 0.5, 0.5},
        {0.5,-0.5, 0.5}
    };

    int i;
    //int j = 0;
    //int k = 0;

    for (i = 0; i < 36; i++) {
        // Color logic removed.
        //if (j == 6) {
        //    j = 0;
        //    k++;
        //}
        //glColor3f(colors[k][0], colors[k][1], colors[k][2]);
        glVertex3f(triangles[i][0], triangles[i][1], triangles[i][2]);
        //j++;
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
