#include <stdlib.h>

#include "types.h"
#include "macros.h"

triangle *get_triangles() {
	triangle *triangles = malloc(sizeof(triangle) * TRI_NUM);
	triangles[0] = ((triangle) {(set) {0, 0, 0}, (set) {1, 0, 0}, (set) {0, 0, 1}});
	triangles[1] = ((triangle) {(set) {1, 0, 0}, (set) {1, 0, 1}, (set) {0, 0, 1}});
	triangles[2] = ((triangle) {(set) {-0.1,-0.1,-0.1}, (set) {-0.1,-0.1, 0.1}, (set) {-0.1, 0.1, 0.1}});
	triangles[3] = ((triangle) {(set) {0.1, 0.1,-0.1}, (set) {-0.1,-0.1,-0.1}, (set) {-0.1, 0.1,-0.1}});
	triangles[4] = ((triangle) {(set) {0.1,-0.1, 0.1}, (set) {-0.1,-0.1,-0.1}, (set) {0.1,-0.1,-0.1}});
	triangles[5] = ((triangle) {(set) {0.1, 0.1,-0.1}, (set) {0.1,-0.1,-0.1}, (set) {-0.1,-0.1,-0.1}});
	triangles[6] = ((triangle) {(set) {-0.1,-0.1,-0.1}, (set) {-0.1, 0.1, 0.1}, (set) {-0.1, 0.1,-0.1}});
	triangles[7] = ((triangle) {(set) {0.1,-0.1, 0.1}, (set) {-0.1,-0.1, 0.1}, (set) {-0.1,-0.1,-0.1}});
	triangles[8] = ((triangle) {(set) {-0.1, 0.1, 0.1}, (set) {-0.1,-0.1, 0.1}, (set) {0.1,-0.1, 0.1}});
	triangles[9] = ((triangle) {(set) {0.1, 0.1, 0.1}, (set) {0.1,-0.1,-0.1}, (set) {0.1, 0.1,-0.1}});
	triangles[10] = ((triangle) {(set) {0.1,-0.1,-0.1}, (set) {0.1, 0.1, 0.1}, (set) {0.1,-0.1, 0.1}});
	triangles[11] = ((triangle) {(set) {0.1, 0.1, 0.1}, (set) {0.1, 0.1,-0.1}, (set) {-0.1, 0.1,-0.1}});
	triangles[12] = ((triangle) {(set) {0.1, 0.1, 0.1}, (set) {-0.1, 0.1,-0.1}, (set) {-0.1, 0.1, 0.1}});
	triangles[13] = ((triangle) {(set) {0.1, 0.1, 0.1}, (set) {-0.1, 0.1, 0.1}, (set) {0.1,-0.1, 0.1}});
	return triangles;
}

light *get_lights() {
	light *lights = malloc(sizeof(light) * LIGHT_NUM);
	lights[0] = ((light){(set) {.5, .5, 1.5}, .1});
	return lights;
}
