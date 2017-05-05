#include <GL/glut.h>

#include <stdbool.h>

#include "types.h"
#include "ops.h"
#include "tracer.h"
#include "macros.h"
#include "objects.h"

void draw_pixel(float x,float y,float r,float g,float b) {
#define SZ  .004
	glBegin(GL_TRIANGLES);
	glColor3f(1,0,0);
	glColor3f(r,g,b);
	glVertex2f(-1.0+SZ*(float)x,     -1.0+SZ*(float)y);
	glVertex2f(-1.0+SZ*(float)x,     -1.0+SZ*(float)y+ SZ);
	glVertex2f(-1.0+SZ*(float)x+ SZ, -1.0+SZ*(float)y);
	glVertex2f(-1.0+SZ*(float)x+ SZ, -1.0+SZ*(float)y);
	glVertex2f(-1.0+SZ*(float)x+ SZ, -1.0+SZ*(float)y+ SZ);
	glVertex2f(-1.0+SZ*(float)x,     -1.0+SZ*(float)y+ SZ);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	float x,y;
	triangle *triangles = get_triangles();
	light *lights = get_lights();
	set eye = (set) { .5, .5, -1 };
	for (x = 0; x <= 1; x += .002) {
		for (y = 0; y <= 1; y += .002) {
			set pt = (set) { x, y, 0 };
			float b = ray(pt, eye, triangles, lights);
			draw_pixel(x*500, y*500, b,b,b);
		}
	}
	free(triangles);
	free(lights);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutMainLoop();
}
