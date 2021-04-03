from PIL import Image
import numpy as np


class Sandpile(object):
    def __init__(self, area):
        self.area = area
        self.matrix = []
        for i in range(self.area[0]):
            self.matrix.append([0] * self.area[1])

    def landslide(self, point):
        sz_x, sz_y = self.area
        x, y = point
        if x == 0 and 1 < y < sz_y:
            self.matrix[x][y] -= 4
            self.matrix[x][y + 1] += 1
            self.matrix[x][y - 1] += 1
            self.matrix[x + 1][y] += 1
            return
        if y == 0 and 1 < x < sz_x:
            self.matrix[x][y] -= 4
            self.matrix[x][y + 1] += 1
            self.matrix[x + 1][y] += 1
            self.matrix[x - 1][y] += 1
            return
        # normal
        self.matrix[x][y] -= 4
        self.matrix[x + 1][y] += 1
        self.matrix[x - 1][y] += 1
        self.matrix[x][y + 1] += 1
        self.matrix[x][y - 1] += 1

    def landslide(self, point, num):
        sz_x, sz_y = self.area
        x, y = point
        tmp = num // 4
        self.matrix[x][y] = num % 4
        if (0 < x < sz_x - 1) and (0 < y < sz_y - 1):
            self.matrix[x + 1][y] += tmp
            self.matrix[x - 1][y] += tmp
            self.matrix[x][y + 1] += tmp
            self.matrix[x][y - 1] += tmp

    def color_render(self, colors):
        new_matrix = np.zeros((len(self.matrix), len(self.matrix[0]), 3), dtype=np.uint8)
        for i in range(len(new_matrix)):
            for j in range(len(new_matrix[0])):
                new_matrix[i][j] = colors[self.matrix[i][j]]
        return new_matrix


def move_system_point(size, step, point):
    ans = (size[0] // 2 + point[0] * step, size[1] // 2 + point[1] * step)
    return ans


if __name__ == '__main__':
    window_size = (120, 120)
    size_iteration = 10 ** 14
    sand = Sandpile(window_size)
    centre = move_system_point(window_size, 1, (0, 0))
    sand.landslide(centre, num=size_iteration)
    is_not_relaxed = True
    while is_not_relaxed:
        is_not_relaxed = False
        for i in range(window_size[0]):
            for j in range(window_size[1]):
                tmp = sand.matrix[i][j]
                if tmp > 3:
                    is_not_relaxed = True
                    sand.landslide((i, j), tmp)

    colors = [(255, 255, 0), (0, 125, 52), (0, 125, 255), (139, 0, 255)]
    img = Image.fromarray(sand.color_render(colors), "RGB")
    img.show()
