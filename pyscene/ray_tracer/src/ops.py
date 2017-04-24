from .rt_types import *


def cross_product(u, v):
    return Set(((u.y * v.z) - (u.z * v.y)), ((u.z * v.x) - (u.x * v.z)), ((u.x * v.y) - (u.y * v.x)))


def dot_product(u, v):
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z)


def scalar_dot(u, v):
    return Set((u * v.x), (u * v.y), (u * v.z))


def pt_add(a, b):
    return Set((a.x + b.x), (a.y + b.y), (a.z + b.z))


def pt_sub(a, b):
    return Set((a.x - b.x), (a.y - b.y), (a.z - b.z))


def mag(a):
    return math.sqrt(math.pow(a.x, 2) + math.pow(a.y, 2) + math.pow(a.z, 2))


