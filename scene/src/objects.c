#include <stdlib.h>

#include "types.h"
#include "macros.h"

triangle *get_triangles() {
	float x = .2;
	float y = .15;
	float z = .6;
	float length = .1;
	triangle *triangles = malloc(sizeof(triangle) * TRI_NUM);
	triangles[0] = ((triangle) {(set) {0, 0, 0},
			(set) {1, 0, 0},
			(set) {0, 0, 1}});
	triangles[1] = ((triangle) {(set) {1, 0, 0},
			(set) {1, 0, 1},
			(set) {0, 0, 1}});	
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
	triangles[6] = ((triangle) {(set) {x-length,y-length,z-length},
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
	return triangles;
}

light *get_lights() {
	light *lights = malloc(sizeof(light) * LIGHT_NUM);
	lights[0] = ((light){(set) {.5, .5, 1.5}, .1});
	return lights;
}
