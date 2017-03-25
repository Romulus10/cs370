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

float *eye;

float *transform_eye() {
    eye[0] = ((cos(1 * (M_PI/180)) * eye[0]) + (sin(1 * (M_PI/180)) * eye[2]));
    eye[1] = eye[1];
    eye[2] = ((-sin(1 * (M_PI/180)) * eye[0]) + (cos(1 * (M_PI/180)) * eye[2]));
    eye[3] = 1;
}

void draw_triangles() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    static const float vertices[][3] = {
        { 0.5, 0.5, 0.5},
        { 0.5, 0.5,-0.5},
        { 0.5,-0.5, 0.5},
        { 0.5,-0.5,-0.5},
        {-0.5, 0.5, 0.5},
        {-0.5, 0.5,-0.5},
        {-0.5,-0.5, 0.5},
        {-0.5,-0.5,-0.5}
    };

    static const float texcoords[][2] = {
        {0.0, 1.0},
        {1.0, 1.0},
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 0.0}
    };

    static const int triangles[48] = {
        4,0,6,2,0,6,
        1,5,3,7,5,3,
        4,0,5,1,0,5,
        0,1,2,3,1,2,
        5,4,7,6,4,7,
        6,2,7,3,2,7
    };

    int i;
    int j = 0;

    for (i = 0; i < 48; i++) {
        if (j == 6) {
            j = 0;
        } else {
            j++;
        }
        int k = triangles[i];
        glTexCoord2fv(texcoords[j]);
        glVertex3fv(vertices[k]);
    }
    glEnd();
}

void display(void) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 40.0f, 1.0f, 1.0f, 10000.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    int width, height;
    unsigned char* image = SOIL_load_image("pip_boy.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
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

