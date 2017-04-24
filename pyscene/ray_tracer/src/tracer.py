import math

from .ops import *
from .rt_types import *


def intersect(p1, p2, t):
    n = cross_product(pt_sub(t.b, t.a), pt_sub(t.c, t.a))
    r = pt_sub(t.a, p2)
    q = pt_sub(p1, p2)
    u = dot_product(n, r) / dot_product(n, q)
    i = pt_add(p2, scalar_dot(u, pt_sub(p1, p2)))
    v1 = pt_sub(t.a, i)
    v2 = pt_sub(t.b, i)
    v3 = pt_sub(t.c, i)
    c1 = cross_product(v1, v2)
    c2 = cross_product(v2, v3)
    c3 = cross_product(v3, v1)
    d = Set(dot_product(c1, c2), dot_product(c2, c3), dot_product(c3, c1))
    if (d.x >= 0) and (d.y >= 0) and (d.z >= 0):
        return True
    else:
        return False


def light_intersect(p1, p2, i):
    u = ((i.center.x - p1.x) * (p2.x - p1.x) + (i.center.y - p1.y) * (p2.y - p1.y) + (i.center.z - p1.z) * (
        p2.z - p1.z)) / math.pow(mag(pt_sub(p2, p1)), 2)
    point = pt_add(p1, scalar_dot(u, pt_sub(p2, p1)))
    if mag(pt_sub(point, i.center)) <= i.r:
        return True
    else:
        return False


def ray(p1, p2):
    bright = 0
    triangles = [
        Triangle(Set(0, 0, 0), Set(1, 0, 0), Set(0, 0, 1)),
        Triangle(Set(1, 0, 0), Set(1, 0, 1), Set(0, 0, 1))]
    lights = [
        Light(Set(.5, .5, .5), .1)]
    for i in triangles:
        if intersect(p1, p2, i):
            bright = .1
        return bright
    else:
        return 0


