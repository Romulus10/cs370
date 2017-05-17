/*
 * Sean Batzel
 *
 * Ray Tracer - Working/Improved/Optimized Version
 */

#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define LIGHT -1.0
#define TRIANGLE 1.0

#define RES 500
#define INC .002
#define SZ .004

#define TRI_NUM 14
#define LIGHT_NUM 1

#define VECTOR_DIST_SPHERE(R, P1, P2, U)                                       \
  ({                                                                           \
    set_3 a;                                                                   \
    PT_SUB(a, P2, P1);                                                         \
    set_3 b;                                                                   \
    SCALAR_DOT(b, a, U);                                                       \
    PT_ADD(R, P1, b);                                                          \
  });

#define VECTOR_U_SPHERE(R, P1, P2, P3)                                         \
  ({                                                                           \
    float a = ((P3.x - P1.x) * (P2.x - P1.x)) +                                \
              ((P3.y - P1.y) * (P2.y - P1.y)) +                                \
              ((P3.z - P1.z) * (P2.z - P1.z));                                 \
    set_3 sub;                                                                 \
    PT_SUB(sub, P2, P1);                                                       \
    float b;                                                                   \
    MAG(b, sub);                                                               \
    b = pow(b, 2);                                                             \
                                                                               \
    R = a / b;                                                                 \
  })

#define MAG(R, VEC)                                                            \
  ({ R = sqrt(VEC.x * VEC.x + VEC.y * VEC.y + VEC.z * VEC.z); })

#define VECTOR_INTERSECT(R, P1, P2, U)                                         \
  ({                                                                           \
    set_3 arg1, arg2;                                                          \
    PT_SUB(arg1, P2, P1);                                                      \
    SCALAR_DOT(arg2, arg1, U);                                                 \
    PT_ADD(R, P1, arg2);                                                       \
  })

#define VECTOR_U(P, N, T, P1, P2)                                              \
  ({                                                                           \
    float arg1, arg2;                                                          \
    set_3 TminusP1, P2minusP1;                                                 \
    PT_SUB(TminusP1, T, P1);                                                   \
    PT_SUB(P2minusP1, P2, P1);                                                 \
    DOT_PRODUCT(arg1, N, TminusP1);                                            \
    DOT_PRODUCT(arg2, N, P2minusP1);                                           \
    P = arg1 / arg2;                                                           \
  })

#define GET_NORMAL(R, T1, T2, T3)                                              \
  ({                                                                           \
    set_3 a, b;                                                                \
    PT_SUB(a, T2, T1);                                                         \
    PT_SUB(b, T3, T1);                                                         \
    CROSS_PRODUCT(R, a, b);                                                    \
  })

#define CROSS_PRODUCT(R, V1, V2)                                               \
  (R = (set_3){(V1.y * V2.z) - (V1.z * V2.y), (V1.z * V2.x) - (V1.x * V2.z),   \
               (V1.x * V2.y) - (V1.y * V2.x)})

#define DOT_PRODUCT(P, V1, V2)                                                 \
  (P = (V1.x * V2.x) + (V1.y * V2.y) + (V1.z * V2.z))

#define SCALAR_DOT(R, V1, s) (R = (set_3){V1.x * s, V1.y * s, V1.z * s})

#define PT_ADD(R, V1, V2) (R = (set_3){V1.x + V2.x, V1.y + V2.y, V1.z + V2.z})

#define PT_SUB(R, V1, V2) (R = (set_3){V1.x - V2.x, V1.y - V2.y, V1.z - V2.z})

#define CHECK_D(D1, D2, D3) ((d1 > 0) && (d2 > 0) && (d3 > 0))

#define CHECK_SIGN(X, Y) (!((X >= 0) ^ (Y < 0)))

typedef struct set_3 {
  float x;
  float y;
  float z;
} set_3;

typedef struct set_2 {
  float a;
  float b;
} set_2;

typedef struct triangle {
  set_3 t1;
  set_3 t2;
  set_3 t3;
} triangle;

typedef struct light {
  set_3 center;
  float radius;
} light;

typedef struct {
  float u;
  set_3 normal;
  set_3 I;
  bool lit;
  int type;
} inter;

triangle *triangles;
light *lights;

void triangle_x(set_2 v1, set_2 v2, set_2 v3, float plane, triangle *ptr) {
  *(ptr) = ((triangle){.t1 = {plane, v1.a, v1.b},
                       .t2 = {plane, v2.a, v2.b},
                       .t3 = {plane, v3.a, v3.b}});
}

void triangle_y(set_2 v1, set_2 v2, set_2 v3, float plane, triangle *ptr) {
  *(ptr) = ((triangle){.t1 = {v1.a, plane, v1.b},
                       .t2 = {v2.a, plane, v2.b},
                       .t3 = {v3.a, plane, v3.b}});
}

void triangle_z(set_2 v1, set_2 v2, set_2 v3, float plane, triangle *ptr) {
  *(ptr) = (triangle){.t1 = {v1.a, v1.b, plane},
                      .t2 = {v2.a, v2.b, plane},
                      .t3 = {v3.a, v3.b, plane}};
}

void square_z(set_3 center, float offset, triangle *ptr, int dir) {
  float c;
  if (dir == 0) {
    c = center.z;
  } else if (dir < 0) {
    c = center.z - offset;
  } else {
    c = center.z + offset;
  }
  triangle_z(((set_2){.a = center.x - offset, .b = center.y + offset}),
             ((set_2){.a = center.x + offset, .b = center.y + offset}),
             ((set_2){.a = center.x - offset, .b = center.y - offset}), c, ptr);
  triangle_z(((set_2){.a = center.x + offset, .b = center.y + offset}),
             ((set_2){.a = center.x + offset, .b = center.y - offset}),
             ((set_2){.a = center.x - offset, .b = center.y - offset}), c,
             ptr + 1);
}

void square_y(set_3 center, float offset, triangle *ptr, int dir) {
  float c;
  if (dir == 0) {
    c = center.y;
  } else if (dir < 0) {
    c = center.y - offset;
  } else {
    c = center.y + offset;
  }
  triangle_y(((set_2){.a = center.x - offset, .b = center.z + offset}),
             ((set_2){.a = center.x + offset, .b = center.z + offset}),
             ((set_2){.a = center.x - offset, .b = center.z - offset}), c, ptr);
  triangle_y(((set_2){.a = center.x + offset, .b = center.z + offset}),
             ((set_2){.a = center.x + offset, .b = center.z - offset}),
             ((set_2){.a = center.x - offset, .b = center.z - offset}), c,
             ptr + 1);
}

void square_x(set_3 center, float offset, triangle *ptr, int dir) {
  float c;
  if (dir == 0) {
    c = center.x;
  } else if (dir < 0) {
    c = center.x - offset;
  } else {
    c = center.x + offset;
  }
  triangle_x(((set_2){.a = center.y - offset, .b = center.z + offset}),
             ((set_2){.a = center.y + offset, .b = center.z + offset}),
             ((set_2){.a = center.y - offset, .b = center.z - offset}), c, ptr);
  triangle_x(((set_2){.a = center.y + offset, .b = center.z + offset}),
             ((set_2){.a = center.y + offset, .b = center.z - offset}),
             ((set_2){.a = center.y - offset, .b = center.z - offset}), c,
             ptr + 1);
}

void build_cube(set_3 center, float offset, triangle *ptr) {
  square_x(center, offset, ptr, -1);
  square_x(center, offset, ptr + 2, +1);
  square_y(center, offset, ptr + 4, -1);
  square_y(center, offset, ptr + 6, +1);
  square_z(center, offset, ptr + 8, -1);
  square_z(center, offset, ptr + 10, +1);
}

inter intersect(set_3 screen, set_3 eye, int i) {
  inter result;
  set_3 v1, v2, v3, c1, c2, c3;
  float d1, d2, d3;

  set_3 t1 = triangles[i].t1, t2 = triangles[i].t2, t3 = triangles[i].t3;

  GET_NORMAL(result.normal, t1, t2, t3);

  VECTOR_U(result.u, result.normal, t1, eye, screen);

  VECTOR_INTERSECT(result.I, eye, screen, result.u);

  PT_SUB(v1, t1, result.I);
  PT_SUB(v2, t2, result.I);
  PT_SUB(v3, t3, result.I);
  CROSS_PRODUCT(c1, v1, v2);
  CROSS_PRODUCT(c2, v2, v3);
  CROSS_PRODUCT(c3, v3, v1);
  DOT_PRODUCT(d1, c1, c2);
  DOT_PRODUCT(d2, c2, c3);
  DOT_PRODUCT(d3, c3, c1);

  if (CHECK_D(d1, d2, d3)) {
    result.lit = true;
  } else {
    result.lit = false;
  }
  return result;
}

inter intersect_light(set_3 screen, set_3 eye, set_3 center, float radius) {
  inter result;
  float u;
  VECTOR_U_SPHERE(u, eye, screen, center);
  set_3 p;
  VECTOR_DIST_SPHERE(p, eye, screen, u);
  set_3 sub;
  PT_SUB(sub, p, center);
  float sub_mag;
  MAG(sub_mag, sub);
  result.u = u;
  result.lit = sub_mag <= radius;
  return result;
}

float ray(set_3 screen, set_3 eye) {
  float bright = 0;
  inter result, closest;
  closest.u = INFINITY;

  for (int i = 0; i < TRI_NUM; i++) {
    result = intersect(screen, eye, i);
    if (result.u < closest.u && result.u > 0 && result.lit) {
      closest = result;
      closest.type = TRIANGLE;
    }
  }

  for (int i = 0; i < LIGHT_NUM; i++) {
    result = intersect_light(screen, eye, lights[i].center, .1);
    if (result.u < closest.u && result.u > 0 && result.lit) {
      closest = result;
      closest.type = LIGHT;
    }
  }

  if (closest.type == LIGHT) {
    bright = 1;
  }
  if (closest.type == TRIANGLE) {
    bright = .1;

    for (int i = 0; i < LIGHT_NUM; i++) {
      set_3 oldray;
      PT_SUB(oldray, eye, screen);
      set_3 newray;
      PT_SUB(newray, closest.I, lights[i].center);
      float dot_old;
      DOT_PRODUCT(dot_old, oldray, closest.normal);
      float dot_new;
      DOT_PRODUCT(dot_new, newray, closest.normal);

      if (CHECK_SIGN(dot_old, dot_new)) {
        set_3 sub_diff;
        PT_SUB(sub_diff, closest.I, lights[i].center);
        float mag;
        MAG(mag, sub_diff);
        bright += (ray(lights[i].center, closest.I)) / (mag);
      }
    }
  }
  return bright;
}

void init_mod() {
  square_y(((set_3){.x = .5, .y = .0, .z = .5}), .5, triangles, 0);
  build_cube(((set_3){.x = .2, .y = .15, .z = .6}), .1, triangles + 2);
  lights[0] = (light){(set_3){.x = .5, .y = .5, .z = 1.5}};
}

void draw_pixel(float x, float y, float r, float g, float b) {
  glBegin(GL_TRIANGLES);
  glColor3f(r, g, b);
  glVertex2f(-1.0 + SZ * (float)x, -1.0 + SZ * (float)y);
  glVertex2f(-1.0 + SZ * (float)x, -1.0 + SZ * (float)y + SZ);
  glVertex2f(-1.0 + SZ * (float)x + SZ, -1.0 + SZ * (float)y);

  glVertex2f(-1.0 + SZ * (float)x + SZ, -1.0 + SZ * (float)y);
  glVertex2f(-1.0 + SZ * (float)x + SZ, -1.0 + SZ * (float)y + SZ);
  glVertex2f(-1.0 + SZ * (float)x, -1.0 + SZ * (float)y + SZ);
  glEnd();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  set_3 eye = {0.5, 0.5, -1.0};

  for (float i = 0; i < 1.0; i += INC) {
    for (float j = 0; j < 1.0; j += INC) {
      set_3 screen = {i, j, 0};
      float b = ray(screen, eye);
      draw_pixel(i * RES, j * RES, b, b, b);
    }
  }
  glFlush();
}

int main(int argc, char **argv) {
  triangles = (triangle *)malloc(sizeof(triangle) * TRI_NUM);
  lights = (light *)malloc(sizeof(light) * LIGHT_NUM);
  glutInit(&argc, argv);
  glutCreateWindow("ray tracer");
  init_mod();
  glutDisplayFunc(display);
  glutMainLoop();
  free(triangles);
  free(lights);
}
