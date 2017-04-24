import OpenGL
import math

class Set (object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class Triangle (object):
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

class Light (object):
    def __init__(self, center, r):
        self.center = center
        self.r = r

def intersect(p1, p2, i):
	N = cross_product(pt_sub(i.b, i.a), pt_sub(i.c, i.a))
	r = pt_sub(i.a, p2)
	q = pt_sub(p1, p2)
	U = dot_product(N, r) / dot_product(N, q)
	I = pt_add(p2, scalar_dot(U, pt_sub(p1, p2)))
	v1 = pt_sub(i.a, I)
	v2 = pt_sub(i.b, I)
	v3 = pt_sub(i.c, I)
	c1 = cross_product(v1, v2)
	c2 = cross_product(v2, v3)
	c3 = cross_product(v3, v1)
	d = Set(dot_product(c1, c2), dot_product(c2, c3), dot_product(c3, c1))
	if ((d.x >= 0) and (d.y >= 0) and (d.z >= 0)):
		return true
	else:
		return false

def light_intersect(p1, p2, i):
    U = ((i.center.x - p1.x)*(p2.x - p1.x) + (i.center.y - p1.y)*(p2.y - p1.y) + (i.center.z - p1.z)*(p2.z - p1.z)) / math.pow(mag(pt_sub(p2,p1)), 2)
    P = pt_add(p1, scalar_dot(U, pt_sub(p2, p1)))
    if (mag(pt_sub(P, i.center)) <= i.r):
        return true
    else:
        return false

def ray(p1, p2):
    triangles = []
	triangles[0] = Triangle(Set(0, 0, 0), Set(1, 0, 0 ), Set(0, 0, 1))
	triangles[1] = Triangle(Set(1, 0, 0), Set(1, 0, 1 ), Set(0, 0, 1))
	lights = []
	lights[0] = Light(Set(.5, .5, .5), .1)
	for (i = 0 i < TRI_NUM i++):
	    if (intersect(p1, p2, triangles[i])):
	        bright = .1
            N = cross_product(pt_sub(triangles[i].b, triangles[i].a), pt_sub(triangles[i].c, triangles[i].a))
	        return bright
	    else:
	        return 0
	for (i = 0 i < LIGHT_NUM i++):
        if (light_intersect(p1, p2, lights[i])):
            return 1
        else:
            return 0

def cross_product(u, v):
    return Set(((u.y * v.z) - (u.z * v.y)), ((u.z * v.x) - (u.x * v.z)), ((u.x * v.y) - (u.y * v.x)))

def dot_product(u, v):
    return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z))

def scalar_dot(float u, set v) {
    return Set((u * v.x), (u * v.y), (u * v.z))

def pt_add(a, b) {
    return Set((a.x + b.x), (a.y + b.y), (a.z + b.z))

def pt_sub(a, b):
    return Set((a.x - b.x), (a.y - b.y), (a.z - b.z))

def mag(a):
    return math.sqrt(math.pow(a.x, 2) + math.pow(a.y, 2) + math.pow(a.z, 2))

def draw_pixel(x, y, r, g, b):
    SZ = .02
	glBegin(GL_TRIANGLES)
	glColor3f(1,0,0)
	glColor3f(r,g,b)
	glVertex2f(-1.0+.02*x,     -1.0+.02*y)
	glVertex2f(-1.0+.02*x,     -1.0+.02*y+ SZ)
	glVertex2f(-1.0+.02*x+ SZ, -1.0+.02*y)
	glVertex2f(-1.0+.02*x+ SZ, -1.0+.02*y)
	glVertex2f(-1.0+.02*x+ SZ, -1.0+.02*y+ SZ)
	glVertex2f(-1.0+.02*x,     -1.0+.02*y+ SZ)
	glEnd()

def display():
	glClear(GL_COLOR_BUFFER_BIT)
	eye = Set(.5, .5, -1)
	for x in range(5, .01):
		for y in range(5, .01):
			pt = Set(x, y, 0)
			if ray(pt, eye):
				draw_pixel(x*100, y*100, 1,1,1)
			else:
				draw_pixel(x*100, y*100, 0,0,0)
	glFlush()

def main():
	glutInit(sys.argv)
	glutCreateWindow("simple")
	glutDisplayFunc(display)
	glutMainLoop()

