from .rt_types import *
import math


def cross_product(u: Set, v: Set) -> Set:
    """
    :param u: Set
    :param v: Set
    :return: u x v
    """
    return Set(((u.y * v.z) - (u.z * v.y)), ((u.z * v.x) - (u.x * v.z)), ((u.x * v.y) - (u.y * v.x)))


def dot_product(u: Set, v: Set) -> float:
    """
    :param u: Set
    :param v: Set
    :return: u * v
    """
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z)


def scalar_dot(u: float, v: Set) -> Set:
    """
    :param u: Set
    :param v: Set
    :return: u multiplied by all components of v
    """
    return Set((u * v.x), (u * v.y), (u * v.z))


def pt_add(a: Set, b: Set) -> Set:
    """
    :param a: Set
    :param b: Set
    :return: a + b
    """
    return Set((a.x + b.x), (a.y + b.y), (a.z + b.z))


def pt_sub(a: Set, b: Set) -> Set:
    """
    :param a: Set
    :param b: Set
    :return: a - b
    """
    return Set((a.x - b.x), (a.y - b.y), (a.z - b.z))


def mag(a: Set) -> float:
    """
    :param a: Set
    :return: The magnitude of the vector a
    """
    return math.sqrt(math.pow(a.x, 2) + math.pow(a.y, 2) + math.pow(a.z, 2))


def get_max(l: list) -> tuple:
    """
    :param l: list of tuples, (object, float)
    :return: The highest u float value in the list of tuples.
    """
    min_el = (None, 0)
    for x in l:
        if x[1] > min_el[1]:
            min_el = x
            l.remove(x)
        if x[1] == 0:
            l.remove(x)
    return min_el
