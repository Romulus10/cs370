#include <GL/gl.h>
#include <GL/glut.h>

#define STUFF_IS_MOVING 0

#if STUFF_IS_MOVING
#include <unistd.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "gimp_image.h"

extern gimp_image pip_boy;
static GLuint texture;

void render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 10);
    gluLookAt(0, 0, -2,
            0, 0, 2,
            0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2d(1, 1); glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2d(1, 0); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2d(0, 0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2d(0, 1); glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopAttrib();

    glFlush();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[]){2.0, 2.0, 2.0, 0.0});
    glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat[]){1.0, 1.0, 1.0, 0.0});

    //texture = raw_texture_load("pip_boy.data", 200, 256);
    texture = pip_boy;
}

#if STUFF_IS_MOVING
void idle() {
    render();
    usleep((1 / 50.0) * 1000000);
}
#endif

void resize(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void key(unsigned char key, int x, int y) {
    if (key == 'q') exit(0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Texture demo - [q]uit");

    init();
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
#if STUFF_IS_MOVING
    glutIdleFunc(idle);
#endif
    glutKeyboardFunc(key);

    glutMainLoop();

    return 0;
}
