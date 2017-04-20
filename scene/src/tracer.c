#include <stdbool.h>

#include "types.h"
#include "ops.h"
#include "macros.h"

bool ray(set p1, set p2, triangle *triangles) {
    int j;
    for (j = 0; j < TRI_NUM; j++) {
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
            return false;
        }
    }
}

int check_light_collision(set p1, set p2, set p3) {
}

int check_trian_collision(set p1, set p2, triangle i) {
}

int get_brightness() {
	int bright = 0;
	return bright;
}