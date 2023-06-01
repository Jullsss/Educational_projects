import numpy as np
from math import sqrt
import matplotlib.pyplot as plt
import pandas as pd


class Matrix:
    def __init__(self, array):
        self.array = array
        self.height = len(array)
        self.width = len(array[0])

    def __call__(self, i, j):
        return self.array[i][j]

    def invert(self):
        return Matrix(np.linalg.inv(np.array(self.array)))

    def transpose(self):
        res = [[self(j, i) for j in range(self.height)] for i in range(self.width)]
        return Matrix(res)

    def __mul__(self, other):
        if (isinstance(other, (int, float))):
            res = []
            for i in range(self.height):
                row = [self(i, j) * other for j in range(self.width)]
                res.append(row)
            return Matrix(res)
        elif (isinstance(other, Matrix)):
            if (self.width != other.height):
                raise NotImplementedError('Unsupported sizes of matrices')
            res = []
            for i in range(self.height):
                row = []
                for j in range(other.width):
                    num = 0
                    for k in range(self.width):
                        num += self(i, k) * other(k, j)
                    row.append(num)
                res.append(row)
            return Matrix(res)
        else:
            return NotImplemented

    def calculate(self, x1, x2, x3, x4, x5, r):
        res = []
        for i in range(self.height):
            row = []
            for j in range(self.width):
                row.append(self(i, j)(r, x1, x2, x3, x4, x5))
            res.append(row)
        return Matrix(res)

    def __rmul__(self, other):
        if (isinstance(other, (int, float))):
            res = []
            for i in range(self.height):
                row = [self(i, j) * other for j in range(self.width)]
                res.append(row)
            return Matrix(res)
        else:
            return NotImplemented

    def __add__(self, other):
        if (isinstance(other, Matrix)):
            res = []
            for i in range(self.height):
                row = [self(i, j) + other(i, j) for j in range(self.width)]
                res.append(row)
            return Matrix(res)
        else:
            NotImplemented



def f(x1, x2, x3, x4, x5):
    return 100*((x2-x1)**2 + (x3-x1)**2 + (x4-x1)**2 + (x5-x1)**2) + (x1-3)**2

def c1(x1, x2, x3, x4, x5):
    return -x1**2 - x2**2 - x3**2 - x4**2 - x5**2 + x3

def c2(x3):
    return -x3 + 1

def Z_func(r, x1, x2, x3, x4, x5):
    return f(x1, x2, x3, x4, x5) + r(1 / c1(x1, x2, x3, x4, x5) + 1 / c2(x3))

def dir1(x1, x2, x3, x4, x5, n):
    return 1 / (-x1**2 - x2**2 - x3**2 + x3 - x4**2 - x5**2)**n

def dir2(xi, x1):
    return 200*(xi-x1)

def Z_func_x1(r, x1, x2, x3, x4, x5):
    return -200*((x2-x1) + (x3-x1) + (x4-x1) + (x5-x1)) + 2*(x1-3) + 2*x1*r*dir1(x1, x2, x3, x4, x5, 2)

def Z_func_x2(r, x1, x2, x3, x4, x5):
    return dir2(x2, x1) + 2*r*x2*dir1(x1, x2, x3, x4, x5, 2)

def Z_func_x3(r, x1, x2, x3, x4, x5):
    return dir2(x3, x1) + r*(1 / (1-x3)**2 - dir1(x1, x2, x3, x4, x5, 2)+ 2*x3*dir1(x1, x2, x3, x4, x5, 2))

def Z_func_x4(r, x1, x2, x3, x4, x5):
    return dir2(x4, x1) + 2*r*x4*dir1(x1, x2, x3, x4, x5, 2)

def Z_func_x5(r, x1, x2, x3, x4, x5):
    return dir2(x5, x1) + 2*r*x5*dir1(x1, x2, x3, x4, x5, 2)

def Z_func_x1_x1(r, x1, x2, x3, x4, x5):
    return 802 + r*(8*x1**2*dir1(x1, x2, x3, x4, x5, 3) + 2*dir1(x1, x2, x3, x4, x5, 2))

def Z_func_x1_x2(r, x1, x2, x3, x4, x5):
    return 8*x1*x2*r*dir1(x1, x2, x3, x4, x5, 3) - 200

def Z_func_x1_x3(r, x1, x2, x3,x4, x5):
    return -200 - r*x1(4-8*x3)*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x1_x4(r, x1, x2, x3,x4, x5):
    return -200 + 8*x1*x4*r*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x1_x5(r, x1, x2, x3,x4, x5):
    return 8*x1*x5*r*dir1(x1, x2, x3, x4, x5, 3) - 200

def Z_func_x2_x2(r, x1, x2, x3, x4, x5):
    return 200 + r*(8*x2**2*dir1(x1, x2, x3, x4, x5, 3) + 2*dir1(x1, x2, x3, x4, x5, 2))

def Z_func_x2_x3(r, x1, x2, x3, x4, x5):
    return -x2*(4-8*x3)*r*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x2_x4(r, x1, x2, x3, x4, x5):
    return 8*x2*x4*r*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x2_x5(r, x1, x2, x3, x4, x5):
    return 8*x2*x5*r*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x3_x3(r, x1, x2, x3, x4, x5):
    return r*(2*(1-2*x3)**2*dir1(x1, x2, x3, x4, x5, 3) + 2*dir1(x1, x2, x3, x4, x5, 2) + 2*dir1(x1, x2, x3, x4, x5, 2))

def Z_func_x3_x4(r, x1, x2, x3, x4, x5):
    return -(4-8*x3)*x4*r*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x3_x5(r, x1, x2, x3, x4, x5):
    return -(4-8*x3)*x5*r*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x4_x4(r, x1, x2, x3, x4,x5):
    return 200 +r*(8*x4**2*dir1(x1, x2, x3, x4, x5, 3) + 2*dir1(x1, x2, x3, x4, x5, 2))

def Z_func_x4_x5(r, x1, x2, x3, x4, x5):
    return 8*x4*x5*dir1(x1, x2, x3, x4, x5, 3)

def Z_func_x5_x5(r, x1, x2, x3, x4, x5):
    return 200 + r*(8*x5**2*dir1(x1, x2, x3, x4, x5, 3) + 2*dir1(x1, x2, x3, x4, x5, 2))


def sub_diff_matrix(U, V, diff1, diff2, r):
    n = U.width
    res = []
    for i in range(1, n+1):
        row = []
        for j in range(1, n+1):
            if abs(U(0, j-1) - V(0, j - 1)) < 10**(-11):
                params = (r, ) + tuple(V(0, k - 1) for k in range(1, j + 1)) + tuple(U(0, k - 1) for k in range(j + 1, n + 1))
                elem = diff2(i - 1, j - 1)(*params)
            else:
                params1 = (r, ) + tuple(V(0, k - 1) for k in range(1, j)) + tuple(U(0, k - 1) for k in range(j, n + 1))
                params2 = (r, ) + tuple(V(0, k - 1) for k in range(1, j + 1)) + tuple(U(0, k - 1) for k in range(j + 1, n + 1))
                elem = (diff1(0, i - 1)(*params1) - diff1(0, i - 1)(*params2)) / (U(0, j - 1) - V(0, j - 1))
            row.append(elem)
        res.append(row)
    return Matrix(res)

def norm(U1, U2):
    res = 0
    for i in range(U1.width):
        res += (U1(0, i) - U2(0, i)) ** 2
    return sqrt(res)

def stefenson(U_k, k, beta, eps, max_step):
    delta = 1
    r = 1
    values = []
    diff1 = Matrix([[Z_func_x1, Z_func_x2, Z_func_x3, Z_func_x4, Z_func_x5]])

    diff2 = Matrix([[Z_func_x1_x1, Z_func_x1_x2, Z_func_x1_x3, Z_func_x1_x4, Z_func_x1_x5],
                   [Z_func_x1_x2, Z_func_x2_x2,  Z_func_x2_x3,  Z_func_x2_x4,  Z_func_x2_x5],
                    [Z_func_x1_x3, Z_func_x2_x3, Z_func_x3_x3, Z_func_x3_x4, Z_func_x3_x5],
                    [Z_func_x1_x4, Z_func_x2_x4, Z_func_x3_x4, Z_func_x4_x4, Z_func_x4_x5],
                    [Z_func_x1_x5, Z_func_x2_x5, Z_func_x3_x5, Z_func_x4_x5, Z_func_x5_x5]])
    while True:
        diff1_k = diff1.calculate(U_k(0, 0), U_k(0, 1), U_k(0, 2), U_k(0, 3), U_k(0, 4), r)
        V_k = U_k + (-beta) * diff1_k
        J_ij = sub_diff_matrix(U_k, V_k, diff1, diff2, r)
        J_invert = J_ij.invert()
        U_next = U_k.transpose() + delta * (-1) * J_invert*diff1_k.transpose()
        U_next = U_next.transpose()

        if c1(U_next(0, 0), U_next(0, 1), U_next(0, 2), U_next(0, 3), U_next(0, 4)) <= 0 or c2(U_next(0, 2)) <= 0:
            delta /= 2
        else:
            if (norm(U_k, U_next) < eps or k >= max_step):
                print('number of steps: ', k)
                return U_next, values, k
            else:
                print("**************************************************************************")
                print('number of iteration:', k)
                print('argument value ({:.3f}, {:.3f}, {:.3f}, {:.3f}, {:.3f})'.format(U_next.array[0][0],
                                        U_next.array[0][1], U_next.array[0][2], U_next.array[0][3], U_next.array[0][4]))
                print('function value: ', f(U_next.array[0][0], U_next.array[0][1], U_next.array[0][2],
                      U_next.array[0][3], U_next.array[0][4]))
                values.append(f(U_next.array[0][0], U_next.array[0][1], U_next.array[0][2],
                      U_next.array[0][3], U_next.array[0][4]))
                k += 1
                U_k = U_next
                r /= 2


def check_input(U):
    return c1(U(0, 0), U(0, 1), U(0, 2), U(0, 3), U(0, 4)) >= 0 and c2(U(0, 2)) >= 0

print("**************************************************************************")
print("* function to minimize: f(x) = 100*sum_(i=2)^(5)(x(i)-x(1))^2+(x(1)-3)^2 *")
print("*      limitations: c1(x)= -sum_(i=1)^(5)(x(i)^2)-x(3) > 0               *")
print("*                   c2(x)=-x(3) + 1 > 0                                  *")
print("**************************************************************************")
# while True:
    # print("Input starting point (five numbers separated by space)")
    # print("which satisfies limitations:")
    # x1, x2, x3, x4, x5 = [float(x) for x in input().split()]
    # if (check_input(Matrix([[x1, x2, x3, x4, x5]]))):
    #     break
    # else:
    #     print("Incorrect input")

print("Input precision:")
eps = float(input())
print("Input max number of steps:")
max_step = int(input())

betta = 0.01
data = []

for x in np.arange(-0.5, 0.5, 0.01):
    if x == -5:
        print('Start from point (-5, -5, -5, -5, -5)')
    elif not x:
        continue

    x1 = x2 = x3 = x4 = x5 = x
    if not check_input(Matrix([[x1, x2, x3, x4, x5]])):
        print("Point ({:.3f}, {:.3f}, {:.3f}, {:.3f}, {:.3f}) is incorrect input since it does't satisfy limitations".
              format(x1, x2, x3, x4, x5))

        number_of_steps = 0
        x_start = '({:.3f}, {:.3f}, {:.3f}, {:.3f}, {:.3f})'.format(x1, x2, x3, x4, x5)
        x_min = 'Incorrect input'
        f_x_min = 'Incorrect input'

        data.append([number_of_steps, x_start, x_min, f_x_min])
        continue

    x_min, values, k = stefenson(Matrix([[x1, x2, x3, x4, x5]]), 1,  betta, eps, max_step)
    print('the minimum is reached at the point with coordinates:')
    print(x_min.array)

    print('And it is equal :', f(x_min.array[0][0], x_min.array[0][1], x_min.array[0][2], x_min.array[0][3], x_min.array[0][4]))

    # fig = plt.figure(figsize=(20, 8))
    # plt.plot(list(range(len(values))), values)
    # plt.show()

    number_of_steps = k
    x_start = '({:.3f}, {:.3f}, {:.3f}, {:.3f}, {:.3f})'.format(x1, x2, x3, x4, x5)
    x_min_ = '({:.3f}, {:.3f}, {:.3f}, {:.3f}, {:.3f})'.format(x_min.array[0][0], x_min.array[0][1],
                                                                x_min.array[0][2], x_min.array[0][3], x_min.array[0][4])
    f_x_min = str(f(x_min.array[0][0], x_min.array[0][1], x_min.array[0][2], x_min.array[0][3], x_min.array[0][4]))

    data.append([number_of_steps, x_start, x_min_, f_x_min])

columns = ['number of steps', 'х_start', 'x_min', 'f(x_min)']
df = pd.DataFrame(data, columns=columns)
print(df)
writer = pd.ExcelWriter('table2.xlsx', engine='xlsxwriter')
df.to_excel(writer, sheet_name='Sheet1')

# Save the result
writer.save()

