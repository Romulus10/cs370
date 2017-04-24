class Set(object):
    def __init__(self, x: float, y: float, z: float) -> None:
        """
        :param x: float, x value
        :param y: float, y value
        :param z: float, z value
        """
        self.x = x
        self.y = y
        self.z = z

    @property
    def __str__(self) -> str:
        """
        :return: overrides object.__str__()
        """
        return "(" + str(self.x) + ", " + str(self.y) + ", " + str(self.z) + ")"


class Triangle(object):
    def __init__(self, a: Set, b: Set, c: Set) -> None:
        """
        :param a: Set, a vertex
        :param b: Set, a vertex
        :param c: Set, a vertex
        """
        self.a = a
        self.b = b
        self.c = c

    def __str__(self) -> str:
        """
        :return: overrides object.__str__()
        """
        return "(" + str(self.a) + ", " + str(self.b) + ", " + str(self.c) + ")"


class Light(object):
    def __init__(self, center: Set, r: float) -> None:
        """
        :param center: Set, location of the center of the sphere
        :param r: float, radius of the sphere
        """
        self.center = center
        self.r = r

    @property
    def __str__(self) -> str:
        """
        :return: extends object.__str__()
        """
        return str(self.center) + ", " + str(self.r)
