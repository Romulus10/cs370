from OpenGL.GL import *
from OpenGL.GLUT import *

from ray_tracer.src.tracer import *


def draw_pixel(x: float, y: float, r: float, g: float, b: float) -> None:
    """
    :rtype: None
    :param x: float, x coordinate
    :param y: float, y coordinate
    :param r: float, red color value
    :param g: float, green color value
    :param b: float, blue color value
    """
    sz = .02
    glBegin(GL_TRIANGLES)
    glColor3f(1, 0, 0)
    glColor3f(r, g, b)
    glVertex2f(-1.0 + .02 * x, -1.0 + .02 * y)
    glVertex2f(-1.0 + .02 * x, -1.0 + .02 * y + sz)
    glVertex2f(-1.0 + .02 * x + sz, -1.0 + .02 * y)
    glVertex2f(-1.0 + .02 * x + sz, -1.0 + .02 * y)
    glVertex2f(-1.0 + .02 * x + sz, -1.0 + .02 * y + sz)
    glVertex2f(-1.0 + .02 * x, -1.0 + .02 * y + sz)
    glEnd()


def display():
    glClear(GL_COLOR_BUFFER_BIT)
    eye = Set(.5, .5, -1)
    for x in [x * 0.01 for x in range(0, 500)]:
        for y in [x * 0.01 for x in range(0, 500)]:
            pt = Set(x, y, 0)
            if ray(pt, eye):
                draw_pixel(x * 100, y * 100, 1, 1, 1)
            else:
                draw_pixel(x * 100, y * 100, 0, 0, 0)
    glFlush()


def main():
    glutInit(sys.argv)
    glutCreateWindow(b'simple')
    glutDisplayFunc(display)
    glutMainLoop()


if __name__ == "__main__":
    main()
