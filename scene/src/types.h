typedef struct set {
	float x;
	float y;
	float z;
} set;

typedef struct triangle {
	set a;
	set b;
	set c;
} triangle;

typedef struct light {
	set center;
	float r;
} light;
