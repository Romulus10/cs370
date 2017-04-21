#include <GL/glut.h>

#include <stdbool.h>

#include "types.h"
#include "ops.h"
#include "tracer.h"
#include "macros.h"

void draw_pixel(float x,float y,float r,float g,float b) {
    #define SZ  .02
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glColor3f(r,g,b);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    float x,y;
    set eye = (set) { .5, .5, -1 };
    triangle *triangles = malloc(sizeof(triangle) * TRI_NUM);
    triangles[0] = (triangle){(set) { 0, 0, 0 },  (set) { 1, 0, 0 }, (set) { 0, 0, 1 }};
    triangles[1] = (triangle){(set) { 1, 0, 0 },  (set) { 1, 0, 1 }, (set) { 0, 0, 1 }};
    light *lights = malloc(sizeof(light) * LIGHT_NUM);
    lights[0] = (light) { (set) { .5, .5, 1.5 }, .1 };
    for (x = 0; x <= 1; x += .01) {
        for (y = 0; y <= 1; y += .01) {
            set pt = (set) { x, y, 0 };
            if (ray(pt, eye, triangles)) {
                draw_pixel(x*100, y*100, 1,1,1);
            } else {
                draw_pixel(x*100, y*100, 0,0,0);
            }
        }
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMainLoop();
}
