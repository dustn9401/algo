board = []
for i in range(9):
    board.append(list(map(int, input().split())))

res = '\n'.join([' '.join(map(str, row)) for row in board])
print(res)
