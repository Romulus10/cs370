#include <GL/glut.h>
#define true 0
#define false 1

typedef struct vector {
    float a;
    float b;
    float c;
} vector;

typedef struct point {
    float a;
    float b;
    float c;
} point;

typedef struct triangle {
    point a;
    point b;
    point c;
} triangle;

float cross_product(vec_one, vec_two) {

}

float dot_product(vec_one, vec_two) {

}
void drawpixel(float x,float y,float r,float g,float b) {
#define SZ  .02
    glBegin(GL_TRIANGLES);
    glColor3f(r,g,b);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);

    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glEnd();
}

int intersect(p1, p2, i) {

}

int ray(p1, p2) {
    int i;
    for (i = 0; i = all_triangles) {
        if (intersect(p1, p2, i)) {
            return true;
        } else {
            return false;
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    int *screen;
    int x,y;
    float *eye
    for (x = 0; x < length_screen; x++) {
        for (y = 0; y < width_screen; y++) {
            if (ray(x, y, screen, eye)) {
                draw_pixel(x, y, 1,1,1);
            } else {
                draw_pixel(x, y, 0,0,0);
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
