#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define LIGHT -1.0
#define TRIANGLE 1.0

#define INC 0.001
#define SZ 0.002
#define RES 1000

#define TRI_NUM 14
#define LIGHT_NUM 1

#define VECTOR_DIST_SPHERE(R, P1, P2, U)                                       \
  ({                                                                           \
    set_3 sr1;                                                                 \
    VECTOR_SUBTRACT(sr1, P2, P1);                                              \
                                                                               \
    set_3 mr1;                                                                 \
    VECTOR_MULTIPLY_S(mr1, sr1, U);                                            \
    VECTOR_ADD(R, P1, mr1);                                                    \
  });

#define VECTOR_U_SPHERE(R, P1, P2, P3)                                         \
  ({                                                                           \
    float top_result = ((P3.x - P1.x) * (P2.x - P1.x)) +                       \
                       ((P3.y - P1.y) * (P2.y - P1.y)) +                       \
                       ((P3.z - P1.z) * (P2.z - P1.z));                        \
                                                                               \
    set_3 bot_v_sub;                                                           \
    VECTOR_SUBTRACT(bot_v_sub, P2, P1);                                        \
                                                                               \
    float bot_result;                                                          \
    VECTOR_MAG(bot_result, bot_v_sub);                                         \
    bot_result = bot_result * bot_result;                                      \
                                                                               \
    R = top_result / bot_result;                                               \
  })

#define VECTOR_MAG(R, VEC)                                                     \
  ({ R = sqrt(VEC.x * VEC.x + VEC.y * VEC.y + VEC.z * VEC.z); })

#define VECTOR_DS(D1, D2, D3, C1, C2, C3)                                      \
  ({                                                                           \
    VECTOR_DOT(D1, C1, C2);                                                    \
    VECTOR_DOT(D2, C2, C3);                                                    \
    VECTOR_DOT(D3, C3, C1);                                                    \
  })

#define VECTOR_CS(C1, C2, C3, V1, V2, V3)                                      \
  ({                                                                           \
    VECTOR_CROSS(C1, V1, V2);                                                  \
    VECTOR_CROSS(C2, V2, V3);                                                  \
    VECTOR_CROSS(C3, V3, V1);                                                  \
  })

#define VECTOR_VS(V1, V2, V3, T1, T2, T3, I)                                   \
  ({                                                                           \
    VECTOR_SUBTRACT(V1, T1, I);                                                \
    VECTOR_SUBTRACT(V2, T2, I);                                                \
    VECTOR_SUBTRACT(V3, T3, I);                                                \
  })

#define VECTOR_INTERSECT(R, P1, P2, U)                                         \
  ({                                                                           \
    set_3 arg1, arg2;                                                          \
    VECTOR_SUBTRACT(arg1, P2, P1);                                             \
    VECTOR_MULTIPLY_S(arg2, arg1, U);                                          \
    VECTOR_ADD(R, P1, arg2);                                                   \
  })

#define VECTOR_U(P, N, T, P1, P2)                                              \
  ({                                                                           \
    float arg1, arg2;                                                  \
    set_3 TminusP1, P2minusP1;                         \
    VECTOR_SUBTRACT(TminusP1, T, P1);                                          \
    VECTOR_SUBTRACT(P2minusP1, P2, P1);                                        \
    VECTOR_DOT(arg1, N, TminusP1);                                             \
    VECTOR_DOT(arg2, N, P2minusP1);                                            \
    P = arg1 / arg2;                                                           \
  })

#define VECTOR_NORMAL(R, T1, T2, T3)                                           \
  ({                                                                           \
    set_3 arg1, arg2;                                  \
    VECTOR_SUBTRACT(arg1, T2, T1);                                             \
    VECTOR_SUBTRACT(arg2, T3, T1);                                             \
    VECTOR_CROSS(R, arg1, arg2);                                               \
  })

#define VECTOR_CROSS(R, V1, V2)                                                \
  (R = (set_3){(V1.y * V2.z) - (V1.z * V2.y), (V1.z * V2.x) - (V1.x * V2.z),   \
               (V1.x * V2.y) - (V1.y * V2.x)})

#define VECTOR_DOT(P, V1, V2)                                                  \
  (P = (V1.x * V2.x) + (V1.y * V2.y) + (V1.z * V2.z))

#define VECTOR_MULTIPLY_S(R, V1, s) (R = (set_3){V1.x * s, V1.y * s, V1.z * s})

#define VECTOR_ADD(R, V1, V2)                                                  \
  (R = (set_3){V1.x + V2.x, V1.y + V2.y, V1.z + V2.z})

#define VECTOR_SUBTRACT(R, V1, V2)                                             \
  (R = (set_3){V1.x - V2.x, V1.y - V2.y, V1.z - V2.z})

#define CHECK_D(D1, D2, D3) ((d1 > 0) && (d2 > 0) && (d3 > 0))

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
  int ind;
} inter;

bool check_sign(float x, float y) { return (!((x >= 0) ^ (y < 0))); }

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
  float centerOff;
  if (dir == 0) {
    centerOff = center.z;
  } else if (dir < 0) {
    centerOff = center.z - offset;
  } else {
    centerOff = center.z + offset;
  }
  triangle_z(((set_2){.a = center.x - offset, .b = center.y + offset}),
             ((set_2){.a = center.x + offset, .b = center.y + offset}),
             ((set_2){.a = center.x - offset, .b = center.y - offset}),
             centerOff, ptr);

  triangle_z(((set_2){.a = center.x + offset, .b = center.y + offset}),
             ((set_2){.a = center.x + offset, .b = center.y - offset}),
             ((set_2){.a = center.x - offset, .b = center.y - offset}),
             centerOff, ptr + 1);
}

void square_y(set_3 center, float offset, triangle *ptr, int dir) {
  float centerOff;
  if (dir == 0) {
    centerOff = center.y;
  } else if (dir < 0) {
    centerOff = center.y - offset;
  } else {
    centerOff = center.y + offset;
  }
  triangle_y(((set_2){.a = center.x - offset, .b = center.z + offset}),
             ((set_2){.a = center.x + offset, .b = center.z + offset}),
             ((set_2){.a = center.x - offset, .b = center.z - offset}),
             centerOff, ptr);

  triangle_y(((set_2){.a = center.x + offset, .b = center.z + offset}),
             ((set_2){.a = center.x + offset, .b = center.z - offset}),
             ((set_2){.a = center.x - offset, .b = center.z - offset}),
             centerOff, ptr + 1);
}

void square_x(set_3 center, float offset, triangle *ptr, int dir) {
  float centerOff;
  if (dir == 0) {
    centerOff = center.x;
  } else if (dir < 0) {
    centerOff = center.x - offset;
  } else {
    centerOff = center.x + offset;
  }
  triangle_x(((set_2){.a = center.y - offset, .b = center.z + offset}),
             ((set_2){.a = center.y + offset, .b = center.z + offset}),
             ((set_2){.a = center.y - offset, .b = center.z - offset}),
             centerOff, ptr);

  triangle_x(((set_2){.a = center.y + offset, .b = center.z + offset}),
             ((set_2){.a = center.y + offset, .b = center.z - offset}),
             ((set_2){.a = center.y - offset, .b = center.z - offset}),
             centerOff, ptr + 1);
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
  inter result = {0.0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, false, 0, 0};

  set_3 t1 = triangles[i].t1, t2 = triangles[i].t2,
        t3 = triangles[i].t3;

  VECTOR_NORMAL(result.normal, t1, t2, t3);

  VECTOR_U(result.u, result.normal, t1, eye, screen);

  VECTOR_INTERSECT(result.I, eye, screen, result.u);

  set_3 v1, v2, v3, c1, c2, c3;

  float d1, d2, d3;

  VECTOR_VS(v1, v2, v3, t1, t2, t3, result.I);
  VECTOR_CS(c1, c2, c3, v1, v2, v3);
  VECTOR_DS(d1, d2, d3, c1, c2, c3);

  if (CHECK_D(d1, d2, d3)) {
    result.lit = true;
  } else {
    result.lit = false;
  }
  return result;
}

inter intersect_light(set_3 screen, set_3 eye, set_3 center, float radius) {
  inter result = (inter){.u = 0.0, .lit = false};
  float u;
  VECTOR_U_SPHERE(u, eye, screen, center);
  set_3 p;
  VECTOR_DIST_SPHERE(p, eye, screen, u);
  set_3 sub;
  VECTOR_SUBTRACT(sub, p, center);
  float sub_mag;
  VECTOR_MAG(sub_mag, sub);
  result.u = u;
  result.lit = sub_mag <= radius;
  return result;
}

float ray(set_3 screen, set_3 eye) {
  float bright = 0.0;
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
    bright = 1.0;
  }
  if (closest.type == TRIANGLE) {
    bright = 0.1;

    for (int i = 0; i < LIGHT_NUM; i++) {
      set_3 oldray;
      VECTOR_SUBTRACT(oldray, eye, screen);
      set_3 newray;
      VECTOR_SUBTRACT(newray, closest.I, lights[i].center);
      float dot_old;
      VECTOR_DOT(dot_old, oldray, closest.normal);
      float dot_new;
      VECTOR_DOT(dot_new, newray, closest.normal);

      if (check_sign(dot_old, dot_new)) {
        set_3 sub_diff;
        VECTOR_SUBTRACT(sub_diff, closest.I, lights[i].center);
        float mag;
        VECTOR_MAG(mag, sub_diff);
        bright += (ray(lights[i].center, closest.I)) / (mag);
      }
    }
  }
  return bright;
}

void init_mod() {
  square_y(((set_3){.x = 0.5, .y = 0.0, .z = 0.5}), 0.5, triangles, 0);
  build_cube(((set_3){.x = 0.2, .y = 0.15, .z = 0.6}), 0.1, triangles + 2);
  lights[0] = (light){(set_3){.x = 0.5, .y = 0.5, .z = 1.5}};
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
  triangles = malloc(sizeof(triangle) * TRI_NUM);
  lights = malloc(sizeof(light) * LIGHT_NUM);
  glutInit(&argc, argv);
  glutCreateWindow("ray tracer");
  init_mod();
  glutDisplayFunc(display);
  glutMainLoop();
  free(triangles);
  free(lights);
}
