#include <GL/glut.h>

#include <stdio.h>

// Simulates a boolean datatype.
typedef int bool;
#define true 1
#define false 0

#define TRI_NUM 1

typedef struct set {
    /*
     * Universal structure used
     * to implement both points
     * and vectors.
     */
    float x;
    float y;
    float z;
} set;

typedef struct triangle {
    /*
     * A collection of sets
     * representing a triangle.
     */
    set a;
    set b;
    set c;
} triangle;

void print_set(set x, bool y) {
    printf("{%f, %f, %f}", x.x, x.y, x.z);
    if (y) printf("\n");
}

void print_triangle(triangle x) {
    printf("{\n");
    print_set(x.a, true);
    print_set(x.b, true);
    print_set(x.c, true);
    printf("}\n");
}

set cross_product(set u, set v) {
    set r;
    r.x = ((u.y * v.z) - (u.z * v.y));
    r.y = ((u.z * v.x) - (u.x * v.z));
    r.z = ((u.x * v.y) - (u.y * v.x));
    return r;
}

float dot_product(set u, set v) {
    float r = ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
    return r;
}

set scalar_dot(float u, set v) {
    set r = (set) { (u * v.x), (u * v.y), (u * v.z) };
    return r;
}

set pt_add(set a, set b) {
    set r;
    r.x = a.x + b.y;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

set pt_sub(set a, set b) {
    set r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

// Ray Tracer Code

void draw_pixel(float x,float y,float r,float g,float b) {
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

bool intersect(set p1, set p2, triangle i) {
    /*
     * Stretched this out a lot to try to
     * debug it. I don't know what step
     * it's going wrong on, which this
     * should help.
     */
    set p = pt_sub(i.b, i.a);
    set q = pt_sub(i.c, i.a);
    set N = cross_product(p, q);
    set a = pt_sub(i.a, p1);
    float r = dot_product(N, a);
    set m = pt_sub(p2,p1);
    float e = dot_product(N, m);
    float U = r / e;
    set y = pt_sub(p2,p1);
    set s = scalar_dot(U, y);
    set I = pt_add(p1, s);
    set v1 = pt_sub(i.a, I);
    set v2 = pt_sub(i.b, I);
    set v3 = pt_sub(i.c, I);
    set c1 = cross_product(v1, v2);
    set c2 = cross_product(v2, v3);
    set c3 = cross_product(v3, v1);
    set d = (set){dot_product(c1, c2), dot_product(c2, c3), dot_product(c3, c1)};
    if (d.x == 0) d.x = 0;
    if (d.y == 0) d.y = 0;
    if (d.z == 0) d.z = 0;
    if ((d.x > 0) && (d.y > 0) && (d.z > 0)) {
        return true;
    } else {
        return false;
    }
}

bool ray(set p1, set p2, triangle *triangles) {
    int i;
    for (i = 0; i < TRI_NUM; i++) {
        if (intersect(p1, p2, triangles[i])) {
            return true;
        } else {
            return false;
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    float x,y;
    set eye;
    eye.x = 0.5;
    eye.y = 0.5;
    eye.z = -2.0;
    triangle *triangles = malloc(sizeof(triangle) * TRI_NUM);
    triangles[0] = (triangle){(set) { 1, 0, 6 },  (set) { 0.5, 1, 6 }, (set) { 0, 0, 6 }};
    for (x = 0; x < 1; x += .01) {
        for (y = 0; y < 1; y += .01) {
            set pt;
            pt.x = x;
            pt.y = y;
            pt.z = 0;
            if (ray(eye, pt, triangles)) {
                draw_pixel(x*100, y*100, 1,1,1);
            } else {
                draw_pixel(x*100, y*100, 0,0,0);
            }
        }
    }
    glFlush();
}

bool assert_eq_float(float a, float b) {
    if (a == b) {
        return true;
    } else {
        return false;
    }
}

bool assert_set_eq(set a, set b) {
    if (a.x == b.x && a.y == b.y && a.z == b.z) {
        return true;
    } else {
        return false;
    }
}

bool assert_true(bool r) {
    return r;
}

bool assert_false(bool r) {
    return !r;
}

void run_tests() {
    int failed = 6;
    int done = failed;
    set p1 = (set) { 0, 0, 0 };
    set p2 = (set) { 1, 1, 1 };
    set p3 = (set) { 1, 1, 1 };
    set p4 = (set) { 5, 5, 5 };
    set p5 = (set) { .5, .5, -2 };
    set p6 = (set) { .5, .5, 0 };
    triangle tr = (triangle) { (set){1, 1, 0}, (set){1, -1, 0}, (set){-1, -1, 0}};
    assert_set_eq(pt_add(p1, p2), p3) ? failed-- : printf("pt_add fails.\n");
    assert_set_eq(pt_sub(p3, p2), p1) ? failed-- : printf("pt_sub fails.\n");
    assert_true(intersect(p5, p1, tr)) ? failed-- : printf("intersect fails.\n");
    assert_true(intersect(p5, p6, tr)) ? failed-- : printf("intersect fails.\n");
    assert_set_eq(cross_product(p1, p2), p1) ? failed-- : printf("cross_product fails.\n");
    assert_set_eq(scalar_dot(5, p2), p4) ? failed-- : printf("scalar_dot fails.\n");

    if (failed > 0) {
        printf("%d/%d tests failed.\n", failed, done);
    } else {
        printf("Passed all tests.\n");
    }
}

int main(int argc, char** argv) {
    run_tests();
    glutInit(&argc,argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMainLoop();
}
