#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "types.h"
#include "ops.h"
#include "macros.h"
#include "objects.h"

float intersect(set p1, set p2, triangle i) {
	set N = get_normal(i);
	float U = dot_product(N, pt_sub(i.a, p2)) / dot_product(N, pt_sub(p1, p2));
	set I = pt_add(p2, scalar_dot(U, pt_sub(p1, p2)));
	set v1 = pt_sub(i.a, I);
	set v2 = pt_sub(i.b, I);
	set v3 = pt_sub(i.c, I);
	set c1 = cross_product(v1, v2);
	set c2 = cross_product(v2, v3);
	set c3 = cross_product(v3, v1);
	set d = (set){dot_product(c1, c2), dot_product(c2, c3), dot_product(c3, c1)};
	if ((d.x >= 0) && (d.y >= 0) && (d.z >= 0)) {
		return U;
	} else {
		return 0;
	}
}

float light_intersect(set p1, set p2, light i) {
	float U = ((i.center.x - p1.x)*(p2.x - p1.x) + \
			(i.center.y - p1.y)*(p2.y - p1.y) + \
			(i.center.z - p1.z)*(p2.z - p1.z)) / \
		  pow(mag(pt_sub(p2,p1)), 2);
	set P = pt_add(p1, scalar_dot(U, pt_sub(p2, p1)));
	if (mag(pt_sub(P, i.center)) <= i.r) {
		return U;
	} else {
		return 0;
	}
}

float ray(set p1, set p2) {
	triangle *triangles = get_triangles();
	light *lights = get_lights();
	int sw = 0;
	float bright = 0;
	float min = 0xffffffff;
	int i;
	triangle t;
	light l;
	for (i = 0; i < TRI_NUM; i++) {
		float u = intersect(p1, p2, triangles[i]);
		if (u < min && u != 0) {
			min = u;
			t = triangles[i];
		}
	}
	for (i = 0; i < LIGHT_NUM; i++) {
		float u = light_intersect(p1, p2, lights[i]);
		if (u < min && u != 0) {
			min = u;
			l = lights[i];
			if (!sw) sw = 1;
		}
	}
	if (sw) bright = 1;
	else {
		bright = .1;
		for (i = 0; i < LIGHT_NUM; i++) {
			set N = get_normal(triangles[i]);
			set I = get_intersect(N, triangles[i], p1, p2);
			if (check_sign_diff((dot_product(pt_sub(p2, p1), N)), (dot_product(pt_sub(I, lights[i].center), N)))) {
				bright += (ray(lights[i].center, I) / mag(pt_sub(I, lights[i].center)));
			}
		}
	}
	free(triangles); free(lights);
	return bright;
}
