import unittest

from ray_tracer import *


class TestTracer(unittest.TestCase):
    def setUp(self):
        self.a = Set(.25, 0, .25)
        self.b = Set(.25, 0, .25)
        self.c = Set(0, 0, 0)
        self.d = Set(0, 0, 0)
        self.x = Set(0, .5, 0)
        self.y = Set(.5, .5, -1)
        self.z = Triangle(Set(0, 0, 0), Set(1, 0, 0), Set(0, 0, 1))

    def tearDown(self):
        pass

    def test_intersect1(self):
        self.assertFalse(intersect(self.x, self.y, self.z))

    def test_intersect2(self):
        self.assertTrue(intersect(self.a, self.b, self.z))

    def test_intersect3(self):
        self.assertTrue(intersect(self.c, self.d, self.z))

    def test_intersect_light(self):
        pass


class TestOps(unittest.TestCase):
    def setUp(self):
        self.set1 = Set(1, 1, 1)
        self.x = Set(0, .5, 0)
        self.y = Set(.5, .5, -1)
        self.z = Triangle(Set(0, 0, 0), Set(1, 0, 0), Set(0, 0, 1))

    def tearDown(self):
        pass

    def test_pt_add1(self):
        self.assertEqual(pt_add(self.set1, self.set1).x, 2)

    def test_pt_add2(self):
        self.assertEqual(pt_add(self.set1, self.set1).y, 2)

    def test_pt_add3(self):
        self.assertEqual(pt_add(self.set1, self.set1).z, 2)

    def test_pt_sub1(self):
        self.assertEqual(pt_sub(self.set1, self.set1).x, 0)

    def test_pt_sub2(self):
        self.assertEqual(pt_sub(self.set1, self.set1).y, 0)

    def test_pt_sub3(self):
        self.assertEqual(pt_sub(self.set1, self.set1).z, 0)

    def test_pt_sub4(self):
        self.assertEqual(pt_sub(self.z.b, self.z.a).x, 1)

    def test_pt_sub5(self):
        self.assertEqual(pt_sub(self.z.c, self.z.a).x, 0)

    def test_cross(self):
        self.assertEqual(cross_product(pt_sub(self.z.b, self.z.a), pt_sub(self.z.c, self.z.a)).x, 0)

    def test_mag(self):
        self.assertEqual(mag(self.set1), math.sqrt(3))

    def test_cross1(self):
        self.assertEqual(cross_product(self.set1, self.set1).x, 0)

    def test_cross2(self):
        self.assertEqual(cross_product(self.set1, self.set1).y, 0)

    def test_cross3(self):
        self.assertEqual(cross_product(self.set1, self.set1).z, 0)

    def test_dot(self):
        self.assertEqual(dot_product(self.set1, self.set1), 3)

    def test_scalar_dot(self):
        x = scalar_dot(4, self.set1)
        self.assertTrue(x.x == 4 and x.y == 4 and x.z == 4)


if __name__ == "__main__":
    unittest.main()
