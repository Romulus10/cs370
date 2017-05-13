#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define DEBUG 0
#define GL_TEST 0
#define LIGHT -1.0
#define TRIANGLE 1.0
#define INC 0.001
#define SZ  0.002

#define BUILD_SQUAREZ(center, offset, ptr) ({                    \
    BUILD_TRIANGLEZ(                                              \
        ((struct set_2) {.x=(center.x-offset), .y=(center.y+offset)}),   \
        ((struct set_2) {.x=center.x+offset, .y=center.y-offset}),   \
        ((struct set_2) {.x=center.x-offset, .y=center.y-offset}),   \
        center.z-offset,ptr);                                         \
                                                                  \
    BUILD_TRIANGLEZ(                                              \
        ((struct set_2) {.x=center.x-offset, .y=center.y+offset}),   \
        ((struct set_2) {.x=center.x+offset, .y=center.y-offset}),   \
        ((struct set_2) {.x=center.x-offset, .y=center.y-offset}),   \
        center.z+offset,ptr+1);                                         \
    })

#define BUILD_SQUAREY(center, offset, ptr) ({                  \
    BUILD_TRIANGLEY(                                              \
        ((struct set_2) {.x=center.x-offset, .z=center.z+offset}),   \
        ((struct set_2) {.x=center.x+offset, .z=center.z-offset}),   \
        ((struct set_2) {.x=center.x-offset, .z=center.z-offset}),   \
        center.y-offset, ptr);                                         \
                                                                  \
    BUILD_TRIANGLEY(                                              \
        ((struct set_2) {.x=center.x-offset, .z=center.z+offset}),   \
        ((struct set_2) {.x=center.x+offset, .z=center.z-offset}),   \
        ((struct set_2) {.x=center.x-offset, .z=center.z-offset}),   \
        center.y+offset, ptr+1);                                         \
    })

#define BUILD_SQUAREX(center, offset, ptr) ({                     \
     BUILD_TRIANGLEX(                                             \
        ((struct set_2) {.y=center.y-offset, .z=center.z+offset}),       \
        ((struct set_2) {.y=center.y+offset, .z=center.z-offset}),       \
        ((struct set_2) {.y=center.y-offset, .z=center.z-offset}),       \
        center.x-offset, ptr);                                         \
                                                                  \
    BUILD_TRIANGLEX(                                              \
        ((struct set_2) {.y=center.y-offset, .z=center.z+offset}),       \
        ((struct set_2) {.y=center.y+offset, .z=center.z-offset}),       \
        ((struct set_2) {.y=center.y-offset, .z=center.z-offset}),       \
        center.x+offset, ptr+1);                                         \
    })

#define CHECK_SIGNS(R, X, Y) ({                    \
    R = !((X >= 0) ^ (Y < 0));                     \
    })                                             \

#define VECTOR_TEST_RADIUS(R, P1, P2, P3, RAD) ({  \
    float _u;                                      \
    VECTOR_U_SPHERE(_u, P1, P2, P3);               \
                                                   \
    set_3 _p;                                    \
    VECTOR_DIST_SPHERE(_p, P1, P2, _u);            \
                                                   \
    set_3 _sub;                                  \
    VECTOR_SUBTRACT(_sub, _p, P3);                 \
                                                   \
    float _sub_mag;                                \
    VECTOR_MAG(_sub_mag, _sub);                    \
                                                   \
    R = _sub_mag <= RAD;                           \
    })

#define VECTOR_DIST_SPHERE(R, P1, P2, U) ({   \
    set_3 sr1;                              \
    VECTOR_SUBTRACT(sr1, P2, P1);             \
                                              \
    set_3 mr1;                              \
    VECTOR_MULTIPLY_S(mr1, sr1, U);           \
    VECTOR_ADD(R, P1, mr1);                   \
    });

#define VECTOR_U_SPHERE(R, P1, P2, P3) ({  \
    float top_result =                        \
      ((P3.x - P1.x)*(P2.x-P1.x)) +           \
      ((P3.y-P1.y)*(P2.y-P1.y))   +           \
      ((P3.z-P1.z)*(P2.z-P1.z));              \
                                              \
    set_3 bot_v_sub;                        \
    VECTOR_SUBTRACT(bot_v_sub, P2, P1);       \
                                              \
    float bot_result;                         \
    VECTOR_MAG(bot_result, bot_v_sub);        \
    bot_result = bot_result*bot_result;       \
                                              \
    R = top_result / bot_result;              \
    })

#define VECTOR_MAG(R, VEC) ({                           \
    R = sqrt(VEC.x*VEC.x + VEC.y*VEC.y + VEC.z*VEC.z);  \
    })                                                  \


#define VECTOR_DS(D1, D2, D3, C1, C2, C3) ({      \
  VECTOR_DOT(D1, C1, C2);                         \
  VECTOR_DOT(D2, C2, C3);                         \
  VECTOR_DOT(D3, C3, C1);                         \
})                                                \

#define VECTOR_CS(C1, C2, C3, V1, V2, V3) ({      \
  VECTOR_CROSS(C1, V1, V2);                       \
  VECTOR_CROSS(C2, V2, V3);                       \
  VECTOR_CROSS(C3, V3, V1);                       \
})                                                \

#define VECTOR_VS(V1, V2, V3, T1, T2, T3, I) ({   \
  VECTOR_SUBTRACT(V1, T1, I);                     \
  VECTOR_SUBTRACT(V2, T2, I);                     \
  VECTOR_SUBTRACT(V3, T3, I);                     \
})                                                \

#define VECTOR_INTERSECT(R, P1, P2, U) ({ \
  set_3 arg1, arg2;                     \
  VECTOR_SUBTRACT(arg1, P2, P1);          \
  VECTOR_MULTIPLY_S(arg2, arg1, U);       \
  VECTOR_ADD(R, P1, arg2);                \
})                                        \

#define VECTOR_U(P, N, T, P1, P2) ({      \
  float arg1=0, arg2=0;                   \
  set_3 TminusP1 = {0,0,0},             \
          P2minusP1= {0,0,0};             \
  VECTOR_SUBTRACT(TminusP1, T, P1);       \
  VECTOR_SUBTRACT(P2minusP1, P2, P1);     \
  VECTOR_DOT(arg1, N, TminusP1);          \
  VECTOR_DOT(arg2, N, P2minusP1);         \
  P = arg1 / arg2;                        \
})                                        \

#define VECTOR_NORMAL(R, T1, T2, T3) ({     \
  set_3 arg1={0,0,0}, arg2={0,0,0};       \
  VECTOR_SUBTRACT(arg1, T2, T1);            \
  VECTOR_SUBTRACT(arg2, T3, T1);            \
  VECTOR_CROSS(R, arg1, arg2);              \
})                                          \

#define VECTOR_CROSS(R, V1, V2) ({          \
  R.x = (V1.y * V2.z) - (V1.z * V2.y);      \
  R.y = (V1.z * V2.x) - (V1.x * V2.z);      \
  R.z = (V1.x * V2.y) - (V1.y * V2.x);      \
})                                          \

#define VECTOR_DOT(P, V1, V2) ({            \
  P = (V1.x * V2.x) + (V1.y * V2.y) + (V1.z * V2.z);  \
})                                          \

#define VECTOR_MULTIPLY_S(R, V1, s) ({      \
  R.x = V1.x * s;                           \
  R.y = V1.y * s;                           \
  R.z = V1.z * s;                           \
})                                          \

#define VECTOR_ADD(R, V1, V2) ({            \
  R.x = V1.x + V2.x;                        \
  R.y = V1.y + V2.y;                        \
  R.z = V1.z + V2.z;                        \
})                                          \

#define VECTOR_SUBTRACT(R, V1, V2) ({       \
  R.x = V1.x - V2.x;                        \
  R.y = V1.y - V2.y;                        \
  R.z = V1.z - V2.z;                        \
})                                          \

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
} tTriangle;

typedef struct {
  float u;
  set_3 normal;
  set_3 I;
  bool lit;
  int type;
  int ind;
} tIntersect;

typedef struct {
  tTriangle triangle_arr[1024];
  tTriangle *triangle_data;
  int len;
} asgn5_data;

typedef struct {
  set_3 light_arr[1024];
  set_3 *light_data;
  int len;
} light_data;

asgn5_data triangles = {
  .triangle_data = &triangles.triangle_arr[0],
  .len = 0
};

light_data lights = {
  .light_data = &lights.light_arr[0],
  .len = 0
};

void build_trianglex(set_2 v1, set_2 v2, set_2 v3, float plane, tTriangle *ptr) {
    *(ptr) = ((struct triangle){
          .t1={plane, v1.a, v1.b},
          .t2={plane, v2.a, v2.b},
          .t3={plane, v3.a, v3.b}
        });

}

void build_triangley(set_2 v1, set_2 v2, set_2 v3, float plane, tTriangle *ptr) {
    *(ptr) = ((struct triangle){
      .t1={v1.a, plane, v1.b},
      .t2={v2.a, plane, v2.b},
      .t3={v3.a, plane, v3.b}
    });

}

void build_trianglez(set_2 v1, set_2 v2, set_2 v3, float plane, tTriangle *ptr) {
    *(ptr) = (struct triangle) {
      .t1={v1.a, v1.b, plane},
      .t2={v2.a, v2.b, plane},
      .t3={v3.a, v3.b, plane}
    };

}

void build_squarez(set_3 center, float offset, tTriangle *ptr, int dir) {
    float centerOff;
    if(dir == 0) centerOff = center.z;
    else if (dir < 0) centerOff = center.z - offset;
    else centerOff = center.z + offset;

    build_trianglez(
        ((struct set_2) {.a=center.x-offset, .b=center.y+offset}),
        ((struct set_2) {.a=center.x+offset, .b=center.y+offset}),
        ((struct set_2) {.a=center.x-offset, .b=center.y-offset}),
        centerOff, ptr);

    build_trianglez(
        ((struct set_2) {.a=center.x+offset, .b=center.y+offset}),
        ((struct set_2) {.a=center.x+offset, .b=center.y-offset}),
        ((struct set_2) {.a=center.x-offset, .b=center.y-offset}),
        centerOff, ptr+1);
}

void build_squarey(set_3 center, float offset, tTriangle *ptr, int dir) {
    float centerOff;
    if(dir == 0) centerOff = center.y;
    else if (dir < 0) centerOff = center.y - offset;
    else centerOff = center.y + offset;

    build_triangley(
        ((struct set_2) {.a=center.x-offset, .b=center.z+offset}),
        ((struct set_2) {.a=center.x+offset, .b=center.z+offset}),
        ((struct set_2) {.a=center.x-offset, .b=center.z-offset}),
        centerOff, ptr);

    build_triangley(
        ((struct set_2) {.a=center.x+offset, .b=center.z+offset}),
        ((struct set_2) {.a=center.x+offset, .b=center.z-offset}),
        ((struct set_2) {.a=center.x-offset, .b=center.z-offset}),
        centerOff, ptr+1);

}

void build_squarex(set_3 center, float offset, tTriangle *ptr, int dir) {
    float centerOff;
    if(dir == 0) centerOff = center.x;
    else if (dir < 0) centerOff = center.x - offset;
    else centerOff = center.x + offset;

    build_trianglex(
        ((struct set_2) {.a=center.y-offset, .b=center.z+offset}),
        ((struct set_2) {.a=center.y+offset, .b=center.z+offset}),
        ((struct set_2) {.a=center.y-offset, .b=center.z-offset}),
        centerOff, ptr);

    build_trianglex(
        ((struct set_2) {.a=center.y+offset, .b=center.z+offset}),
        ((struct set_2) {.a=center.y+offset, .b=center.z-offset}),
        ((struct set_2) {.a=center.y-offset, .b=center.z-offset}),
        centerOff, ptr+1);
}

void build_cube(set_3 center, float offset, tTriangle *ptr) {
  build_squarex(center,offset, ptr, -1);
  build_squarex(center,offset, ptr+2, +1);

  build_squarey(center,offset, ptr+4, -1);
  build_squarey(center,offset, ptr+6, +1);

  build_squarez(center,offset, ptr+8, -1);
  build_squarez(center,offset,ptr+10, +1);
}

tIntersect query_intersection(set_3 screen, set_3 eye, int triangle) {

  tIntersect result = { 0.0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, false, 0, 0};

 set_3 t1 = triangles.triangle_data[triangle].t1,
         t2 = triangles.triangle_data[triangle].t2,
         t3 = triangles.triangle_data[triangle].t3;

  VECTOR_NORMAL(result.normal, t1, t2, t3);

  VECTOR_U(result.u, result.normal, t1, eye, screen);

  VECTOR_INTERSECT(result.I, eye, screen, result.u);

  set_3 v1={0, 0, 0}, v2={0, 0, 0}, v3 = {0, 0, 0},
          c1={0,0,0}, c2={0,0,0}, c3={0,0,0};

  float d1=0.0, d2=0.0, d3=0.0;

  VECTOR_VS(v1, v2, v3, t1, t2, t3, result.I);
  VECTOR_CS(c1, c2, c3, v1, v2, v3);
  VECTOR_DS(d1, d2, d3, c1, c2, c3);

  if((d1 > 0) && (d2 > 0) && (d3 > 0)) result.lit = true;
  else result.lit = false;

  return result;
}

tIntersect query_lightray(set_3 screen, set_3 eye, set_3 center, float radius) {
  tIntersect result = { 0.0, false };

  float u; VECTOR_U_SPHERE(u, eye, screen, center);

  set_3 p; VECTOR_DIST_SPHERE(p,eye,screen,u);

  set_3 sub; VECTOR_SUBTRACT(sub, p, center);

  float sub_mag; VECTOR_MAG(sub_mag, sub);

  result.u = u;
  result.lit = sub_mag <= radius;
  return result;
}

float ray(set_3 screen, set_3 eye) {

  float bright = 0.0;

  tIntersect result, closest_u;
  closest_u.u = INFINITY;

  for (int i = 0; i < triangles.len; i++) {
    result = query_intersection(screen, eye, i);
    if(result.u < closest_u.u && result.u > 0 && result.lit){
      closest_u = result;
      closest_u.type = TRIANGLE;
    }
  }

  for (int i = 0; i < lights.len; i++) {
    result = query_lightray(screen, eye, lights.light_data[i], .1);
    if(result.u < closest_u.u && result.u > 0 && result.lit){
      closest_u = result;
      closest_u.type = LIGHT;
    }
  }

  if(closest_u.type == LIGHT)  bright = 1.0;
  if(closest_u.type == TRIANGLE) {
    bright = 0.1;

    for(int i = 0; i < lights.len; i++) {
      set_3 oldray; VECTOR_SUBTRACT(oldray, eye, screen);
      set_3 newray; VECTOR_SUBTRACT(newray, closest_u.I, lights.light_data[i]);
      float dot_old;  VECTOR_DOT(dot_old, oldray, closest_u.normal);
      float dot_new;  VECTOR_DOT(dot_new, newray, closest_u.normal);

      bool differs; CHECK_SIGNS(differs, dot_old, dot_new);

      if(differs) {
        set_3 sub_diff; VECTOR_SUBTRACT(sub_diff, closest_u.I, lights.light_data[i]);
        float mag; VECTOR_MAG(mag, sub_diff);
        bright += (ray(lights.light_data[i], closest_u.I)) / (mag);
      }
    }
  }

  return bright;
}

void init_mod() {

  build_squarey(((struct set_3){.x=0.5, .y=0.0, .z=0.5}), 0.5, triangles.triangle_data, 0);
  build_cube(((struct set_3 ){.x=0.2, .y=0.15, .z=0.6}), 0.1, triangles.triangle_data+2);

  lights.light_data[0] = (struct set_3){.x=0.5, .y=0.5, .z=1.5};
  lights.len += 1;

  triangles.len = 14;
}

void drawpixel(float x,float y,float r,float g,float b) {
  glBegin(GL_TRIANGLES);
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
  set_3 eye = {0.5, 0.5, -1.0};

  for(float i = 0; i < 1.0; i += INC){
    for(float j = 0; j < 1.0; j += INC){
      set_3 screen = {i, j, 0};
      float color = ray(screen, eye);
      drawpixel(i*1000, j*1000, color, color, color);
    }
  }
	glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc,argv);
	glutCreateWindow("Assignment 4");
  init_mod();
	glutDisplayFunc(display);
	glutMainLoop();
}
