#include <math.h>
#include <stdbool.h>

#include "types.h"

set cross_product(set u, set v) {
	return (set) {  ((u.y * v.z) - (u.z * v.y)),
		((u.z * v.x) - (u.x * v.z)),
		((u.x * v.y) - (u.y * v.x)) };
}

float dot_product(set u, set v) {
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

set scalar_dot(float u, set v) {
	return (set) { (u * v.x),
		(u * v.y),
		(u * v.z) };
}

set pt_add(set a, set b) {
	return (set) { (a.x + b.x),
		(a.y + b.y),
		(a.z + b.z) };
}

set pt_sub(set a, set b) {
	return (set) { (a.x - b.x),
		(a.y - b.y),
		(a.z - b.z) };
}

float mag(set a) {
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

set get_normal(triangle i) {
	return cross_product(pt_sub(i.b, i.a), pt_sub(i.c, i.a));
}

set get_intersect(set N, triangle i, set p1, set p2) {
	float U = dot_product(N, pt_sub(i.a, p2)) / dot_product(N, pt_sub(p1, p2));
	return pt_add(p2, scalar_dot(U, pt_sub(p1, p2)));
}

bool check_sign_diff(float x, float y) {
	return (!(x > 0) != !(y > 0));
}
