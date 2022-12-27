import matplotlib.pyplot as plt
import numpy as np
from matplotlib import animation
from mpl_toolkits.mplot3d import Axes3D
import time
from math import sqrt

q = 1.6e-29
h = 0.01
B = np.array([0., 0., 1])
E = np.array([0., 0., 0])
c = 3e10
m = 9.1e-31


# ost : [10., 10., 3e5]
# 90 : [0., 3e5, 0.]
# 180 : [0, 0, 3e5]
class Create:+

    def __init__(self, q, m, h):
        self.v = np.array([10., 10., 3e5])
        self.pos = np.array([0., 0., 0.])
        self.q = q
        self.a = np.array([0., 0., 0.])
        self.m = m
        self.h = h
        self.imp = np.array([0., 0., 0.])

    def euler_move(self):
        self.a = self.q * (E + np.cross(self.v, B)) / self.m
        self.pos += self.v * self.h
        self.v += self.a * self.h

    def top_euler(self):
        h2 = h / 2
        self.a = self.q * (E + np.cross(self.v, B)) / self.m
        self.pos += self.v * h2
        self.v += self.a * h2

    def RK2_move(self):
        self.a = self.q * (E + np.cross(self.v, B)) / self.m
        k1 = self.a * self.h
        kk1 = self.v * self.h
        k2 = self.h * self.q * (E + np.cross(self.v + k1, B)) / self.m
        kk2 = (self.v + k1) * self.h
        self.pos += (kk1 + kk2) / 2
        self.v += (k1 + k2) / 2

    def RK4_move(self):
        self.a = self.q * (E + np.cross(self.v, B)) / self.m
        k1 = self.a * self.h
        kk1 = self.v * self.h
        k2 = self.h * self.q * (E + np.cross(self.v + k1 / 2, B)) / self.m
        kk2 = (self.v + k1 / 2) * self.h
        k3 = self.h * self.q * (E + np.cross(self.v + k2 / 2, B)) / self.m
        kk3 = (self.v + k2 / 2) * self.h
        k4 = self.h * self.q * (E + np.cross(self.v + k3, B)) / self.m
        kk4 = (self.v + k3) * self.h
        self.pos += (kk1 + 2 * kk2 + 2 * kk3 + kk4) / 6
        self.v += (k1 + 2 * k2 + 2 * k3 + k4) / 6

    def move_38(self):
        self.a = self.q * (E + np.cross(self.v, B)) / self.m
        k1 = self.a * self.h
        kk1 = self.v * self.h
        k2 = self.h * self.q * (E + np.cross(self.v + k1 / 3, B)) / self.m
        kk2 = (self.v + k1 / 3) * self.h
        k3 = self.h * self.q * (E + np.cross(self.v - 1 / 3 * k1 + k2, B)) / self.m
        kk3 = (self.v - 1 / 3 * k1 + k2) * self.h
        k4 = self.h * self.q * (E + np.cross(self.v + k1 - k2 + k3, B)) / self.m
        kk4 = (self.v + k1 - k2 + k3) * self.h
        self.pos += (kk1 + 3 * kk2 + 3 * kk3 + kk4) / 8
        self.v += (k1 + 3 * k2 + 3 * k3 + k4) / 8

    def move_Felberg(self):
        self.a = self.q * (E + np.cross(self.v, B)) / self.m
        k1 = self.a * self.h
        kk1 = self.v * self.h

        k2 = self.h * self.q * (E + np.cross(self.v + k1 / 4, B)) / self.m
        kk2 = (self.v + k1 / 4) * self.h

        k3 = self.h * self.q * (E + np.cross(self.v + 3 / 32 * k1 + (9 / 32) * k2, B)) / self.m
        kk3 = (self.v - 1 / 3 * k1 + k2) * self.h

        k4 = self.h * self.q * (
                E + np.cross(self.v + (1932 / 2197) * k1 - (7200 / 2197) * k2 + (7296 / 2197) * k3, B)) / self.m
        kk4 = (self.v + (1932 / 2197) * k1 - (7200 / 2197) * k2 + (7296 / 2197) * k3) * self.h

        k5 = self.h * self.q * (
                E + np.cross(self.v + (439 / 216) * k1 - 8 * k2 + (3680 / 513) * k3 - (845 / 4104) * k4, B)) / self.m
        kk5 = (self.v + (439 / 216) * k1 - 8 * k2 + (3680 / 513) * k3 - (845 / 4104) * k4) * self.h

        k6 = self.h * self.q * (
                E + np.cross(self.v + (8 / 27) * k1 + 2 * k2 - (3544 / 2565) * k3 + (1859 / 4104) * k4 - (11 / 40) * k5,
                             B)) / self.m
        kk6 = (self.v + (8 / 27) * k1 + 2 * k2 - (3544 / 2565) * k3 + (1859 / 4104) * k4 - (11 / 40) * k5) * self.h

        self.pos += (16 / 135) * kk1 + (6656 / 12825) * kk3 + (28561 / 56430) * kk4 - (9 / 50) * kk6 + (2 / 55) * kk5
        self.v += (16 / 135) * k1 + (6656 / 12825) * k3 + (28561 / 56430) * k4 - (9 / 50) * k6 + (2 / 55) * k5

    def moment_impulse(self):
        m_speed = sqrt(self.v[0] ** 2 + self.v[1] ** 2 + self.v[2] ** 2)
        self.imp += m * m_speed

        m_imp = np.cross(self.imp, self.pos)
        return sqrt(m_imp[0] ** 2 + m_imp[1] ** 2 + m_imp[2] ** 2)

    def energy(self):
        m_speed = round(sqrt(self.v[0] ** 2 + self.v[1] ** 2 + self.v[2] ** 2), 4)
        return m * (m_speed ** 2) / 2


lim = 300
creation1 = Create(q, m, h)
arrX1 = []
arrY1 = []
arrZ1 = []
for i in range(lim // 2):
    creation1.euler_move()
    arrX1.append(creation1.pos[0])
    arrY1.append(creation1.pos[1])
    arrZ1.append(creation1.pos[2])

creation2 = Create(q, m, h)
arrX2 = []
arrY2 = []
arrZ2 = []
for i in range(lim):
    creation2.top_euler()
    arrX2.append(creation2.pos[0])
    arrY2.append(creation2.pos[1])
    arrZ2.append(creation2.pos[2])

creation3 = Create(q, m, h)
arrX3 = []
arrY3 = []
arrZ3 = []
for i in range(lim):
    creation3.RK2_move()
    arrX3.append(creation3.pos[0])
    arrY3.append(creation3.pos[1])
    arrZ3.append(creation3.pos[2])

creation4 = Create(q, m, h)
arrX4 = []
arrY4 = []
arrZ4 = []
for i in range(lim):
    creation4.RK4_move()
    arrX4.append(creation4.pos[0])
    arrY4.append(creation4.pos[1])
    arrZ4.append(creation4.pos[2])
    if i % 25 == 0:
        print("Energy = ", creation4.energy())

print()

creation5 = Create(q, m, h)
arrX5 = []
arrY5 = []
arrZ5 = []
for i in range(lim):
    creation5.move_Felberg()
    arrX5.append(creation5.pos[0])
    arrY5.append(creation5.pos[1])
    arrZ5.append(creation5.pos[2])
    if i % 25 == 0:
        print("Moment impulse = ", creation5.moment_impulse())

creation6 = Create(q, m, h)
arrX6 = []
arrY6 = []
arrZ6 = []
for i in range(lim):
    creation6.move_38()
    arrX6.append(creation6.pos[0])
    arrY6.append(creation6.pos[1])
    arrZ6.append(creation6.pos[2])


def two_dimensional():
    plt.plot(arrX1, arrY1, color='blue')  # Euler
    plt.plot(arrX2, arrY2, color='purple')  # top Euler
    plt.plot(arrX3, arrY3, color='red')  # Rk2
    plt.plot(arrX4, arrY4, color='black')  # Rk4
    plt.plot(arrX5, arrY5, color='blue')  # Flb
    plt.show()


def three_dimensional():
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # ax.plot(arrX1, arrY1, arrZ1, color='blue')  # Euler
    ax.plot(arrX2, arrY2, arrZ2, color='purple')  # top Euler
    ax.plot(arrX3, arrY3, arrZ3, color='red')  # Rk2
    ax.plot(arrX4, arrY4, arrZ4, color='black')  # Rk4
    ax.plot(arrX5, arrY5, arrZ5, color='blue')  # Flb

    plt.show()


three_dimensional()
