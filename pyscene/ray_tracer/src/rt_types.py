class Set(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ", " + str(self.z) + ")"


class Triangle(object):
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def __str__(self):
        return "(" + str(self.a) + ", " + str(self.b) + ", " + str(self.c) + ")"


class Light(object):
    def __init__(self, center, r):
        self.center = center
        self.r = r

    def __str__(self):
        return str(self.center) + ", " + str(self.r)
