/*
 * Sean Batzel
 *
 * CMPS 370
 * Rotating Cube - with texture
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "SOIL.h"

float *eye; // I wish this wasn't here but I'll optimize and clean later.

float *transform_eye() {
    // Simplified algorithm for a full y-transform
    // This takes the full matrix multiplication and
    // reduces it down to a manageable number of steps.
    // ISSUE:
    //  math.h trig functions deal in radians.
    //  degrees = radians * (π / 180)
    //  floats lose some precision,
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
     *static const float colors[6][3] = {
     *{1.0f,0.0f,0.0f},
     *{0.0f,1.0f,0.0f},
     *{0.0f,0.0f,1.0f},
     *{1.0f,0.0f,0.0f},
     *{0.0f,1.0f,0.0f},
     *{0.0f,0.0f,1.0f}
     *};
     */

    static const float triangles[36][3] = {
        {-0.5f,-0.5f,-0.5f},
        {-0.5f,-0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f},

        {0.5f, 0.5f,-0.5f},
        {-0.5f,-0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f},

        {0.5f,-0.5f, 0.5f},
        {-0.5f,-0.5f,-0.5f},
        {-0.5f,-0.5f,-0.5f},

        {0.5f, 0.5f,-0.5f},
        {0.5f,-0.5f,-0.5f},
        {-0.5f,-0.5f,-0.5f},

        {-0.5f,-0.5f,-0.5f},
        {-0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f,-0.5f},

        {0.5f,-0.5f, 0.5f},
        {-0.5f,-0.5f, 0.5f},
        {-0.5f,-0.5f,-0.5f},

        {-0.5f, 0.5f, 0.5f},
        {-0.5f,-0.5f, 0.5f},
        {0.5f,-0.5f, 0.5f},

        {0.5f, 0.5f, 0.5f},
        {0.5f,-0.5f,-0.5f},
        {0.5f, 0.5f,-0.5f},

        {0.5f,-0.5f,-0.5f},
        {0.5f, 0.5f, 0.5f},
        {0.5f,-0.5f, 0.5f},

        {0.5f, 0.5f, 0.5f},
        {0.5f, 0.5f,-0.5f},
        {-0.5f, 0.5f,-0.5f},

        {0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f,-0.5f},
        {-0.5f, 0.5f, 0.5f},

        {0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f},
        {0.5f,-0.5f, 0.5f}
    };

    float texcoords[] = {
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 1.0
    };

    int i;
    int j = 0;
    //int k = 0;

    for (i = 0; i < 6; i++) {
        // ...why? Neither j nor k is ever used.
        // just kidding I'm using j now.
        //if (j == 12) {
        //    j = 0;
        //k++;
        //}
        //glColor3f(colors[k][0], colors[k][1], colors[k][2]);
        glTexCoord2f(texcoords[j], texcoords[j+1]);
        glVertex3f(triangles[i][0], triangles[i][1], triangles[i][2]);
        if (j == 12) {
            j = 0;
        }
        j = j + 2;
    }

    glEnd();
    glFlush();
}

void display(void) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 40.0f, 1.0f, 1.0f, 10000.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //printf("%f %f %f\n", eye[0], eye[1], eye[2]);
    gluLookAt( eye[0], eye[1], eye[2],
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
            );

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    draw_triangles();

    transform_eye();

    glutSwapBuffers();
}

void init() {
    eye = malloc(sizeof(float) * 4);
    eye[0] = 5.0f;
    eye[1] = 5.0f;
    eye[2] = 5.0f;
    eye[3] = 1.0f;
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    int width, height;
    unsigned char* image = SOIL_load_image("../assets/pip_boy.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutIdleFunc(glutPostRedisplay);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glutMainLoop();
    free(eye);
}

