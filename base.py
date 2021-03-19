from PIL import Image, ImageDraw, ImageFont

window_size = (523, 523)


def add_chip(point, size, arr):
    if point[0] < 0 or point[0] > size[0] or point[1] < 0 or point[1] > size[1]:
        return False
    arr[point[0]][point[1]] += 1
    if arr[point[0]][point[1]] >= 4:
        arr[point[0]][point[1]] = 0
        add_chip((point[0] + 1, point[1]), size, arr)
        add_chip((point[0] - 1, point[1]), size, arr)
        add_chip((point[0], point[1] + 1), size, arr)
        add_chip((point[0], point[1] - 1), size, arr)


def massive_of_model(size, graph, iteration):
    # arr = [[0] * size[0]] * size[1]
    arr = []
    for i in range(size[0]):
        arr.append([0] * size[1])
    for i in range(iteration):
        for v in graph:
            add_chip(v, size, arr)
    return arr


def move_system_point(size, step, point):
    ans = (size[0] // 2 + point[0] * step, size[1] // 2 + point[1] * step)
    return ans


im = Image.new('RGB', window_size, color='white')
draw_s = ImageDraw.Draw(im)
graph = [move_system_point(window_size, 5, (0, 0))]
model_A = massive_of_model(window_size, graph, 10**4)
for i in range(len(model_A)):
    for j in range(len(model_A[0])):
        if model_A[i][j] == 1:
            draw_s.point([i, j], 'yellow')
        if model_A[i][j] == 2:
            draw_s.point((i, j), 'blue')
        if model_A[i][j] == 3:
            draw_s.point((i, j), 'green')
        if model_A[i][j] == 4:
            draw_s.point((i, j), 'orange')

# im.save('digital_signal.png')
im.show()
