from .rt_types import *
import math


def cross_product(u: Set, v: Set) -> Set:
    return Set(((u.y * v.z) - (u.z * v.y)), ((u.z * v.x) - (u.x * v.z)), ((u.x * v.y) - (u.y * v.x)))


def dot_product(u: Set, v: Set) -> float:
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z)


def scalar_dot(u: float, v: Set) -> Set:
    return Set((u * v.x), (u * v.y), (u * v.z))


def pt_add(a: Set, b: Set) -> Set:
    return Set((a.x + b.x), (a.y + b.y), (a.z + b.z))


def pt_sub(a: Set, b: Set) -> Set:
    return Set((a.x - b.x), (a.y - b.y), (a.z - b.z))


def mag(a: Set) -> float:
    return math.sqrt(math.pow(a.x, 2) + math.pow(a.y, 2) + math.pow(a.z, 2))
