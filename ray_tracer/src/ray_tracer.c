#include <GL/glut.h>

#include <stdbool.h>

#include "types.h"
#include "ops.h"

#define TRI_NUM 14

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

bool ray(set p1, set p2) {
    int j;
    float x = .2;
	float y = .15;
	float z = .6;
	float length = .1;
    triangle *triangles = malloc(sizeof(triangle) * TRI_NUM);
    triangles[0] = (triangle){(set) { 0, 0, 0 },  (set) { 1, 0, 0 }, (set) { 0, 0, 1 }};
    triangles[1] = (triangle){(set) { 1, 0, 0 },  (set) { 1, 0, 1 }, (set) { 0, 0, 1 }};
	triangles[2] = ((triangle) {(set) {x-length,y-length,z-length},
			(set) {x-length,y-length,z+length},
			(set) {x-length,y+length,z+length}});
	triangles[3] = ((triangle) {(set) {x+length,y+length,z-length},
			(set) {x-length,y-length,z-length},
			(set) {x-length,y+length,z-length}});
	triangles[4] = ((triangle) {(set) {x+length,y-length,z+length},
			(set) {x-length,y-length,z-length},
			(set) {x+length,y-length,z-length}});
	triangles[5] = ((triangle) {(set) {x+length,y+length,z-length},
			(set) {x+length,y-length,z-length},
			(set) {x-length,y-length,z-length}});
	triangles[6] = ((triangle) {(set) {x-length,z-length,z-length},
			(set) {x-length,y+length,z+length},
			(set) {x-length,y+length,z-length}});
	triangles[7] = ((triangle) {(set) {x+length,y-length,z+length},
			(set) {x-length,y-length,z+length},
			(set) {x-length,y-length,z-length}});
	triangles[8] = ((triangle) {(set) {x-length,y+length,z+length},
			(set) {x-length,y-length,z+length},
			(set) {x+length,y-length,z+length}});
	triangles[9] = ((triangle) {(set) {x+length,y+length,z+length},
			(set) {x+length,-length,z-length},
			(set) {x+length,+length,z-length}});
	triangles[10] = ((triangle) {(set) {x+length,y-length,z-length},
			(set) {x+length,y+length,z+length},
			(set) {x+length,y-length,z+length}});
	triangles[11] = ((triangle) {(set) {x+length,y+length,z+length},
			(set) {x+length,y+length,z-length},
			(set) {x-length,y+length,z-length}});
	triangles[12] = ((triangle) {(set) {x+length,y+length,z+length},
			(set) {x-length,y+length,z-length},
			(set) {x-length,y+length,z+length}});
	triangles[13] = ((triangle) {(set) {x+length,y+length,z+length},
			(set) {x-length,y+length,z+length},
			(set) {x+length,y-length,z+length}});
    for (j = 0; j <= TRI_NUM; j++) {
        triangle i = triangles[j];
        set N = cross_product(pt_sub(i.b, i.a), pt_sub(i.c, i.a));
        set r = pt_sub(i.a, p2);
        set q = pt_sub(p1, p2);
        float U = dot_product(N, r) / dot_product(N, q);
        set I = pt_add(p2, scalar_dot(U, pt_sub(p1, p2)));
        set v1 = pt_sub(i.a, I);
        set v2 = pt_sub(i.b, I);
        set v3 = pt_sub(i.c, I);
        set c1 = cross_product(v1, v2);
        set c2 = cross_product(v2, v3);
        set c3 = cross_product(v3, v1);
        set d = (set){dot_product(c1, c2), dot_product(c2, c3), dot_product(c3, c1)};
        if ((d.x >= 0) && (d.y >= 0) && (d.z >= 0)) {
            return true;
        } else {
            if (j == TRI_NUM) {
                return false;
            }
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    float x,y;
    set eye = (set) { .5, .5, -2 };
    for (x = 0; x <= 1; x += .01) {
        for (y = 0; y <= 1; y += .01) {
            set pt = (set) { x, y, 0 };
            if (ray(pt, eye)) {
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
