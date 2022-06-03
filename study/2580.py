board = []
for i in range(9):
    row = list(map(int, input().split()))
    row = [num if num > 0 else [] for num in row]
    board.append(row)


def solve(puzzle: []) -> str:
    for row in range(9):
        for col in range(9):
            if type(puzzle[row][col]) == list:
                print(get_candidates(puzzle, col, row))

    return '\n'.join(' '.join(map(str, r)) for r in puzzle)


def get_candidates(puzzle: [], x: int, y: int):
    ret = [i for i in range(9)]
    for e in enumerate_square(puzzle, x, y):
        ret[e - 1] = 0

    for e in enumerate_row(puzzle, y):
        ret[e - 1] = 0

    for e in enumerate_col(puzzle, x):
        ret[e - 1] = 0

    return ret


def enumerate_square(puzzle: [], x: int, y: int):
    x_start = x//3 * 3
    y_start = y//3 * 3
    for xi in range(x_start, x_start + 3):
        for yi in range(y_start, y_start + 3):
            if type(puzzle[x][y]) is int:
                yield puzzle[x][y]


def enumerate_row(puzzle: [], y: int):
    for e in puzzle[y]:
        yield e


def enumerate_col(puzzle: [], x: int):
    for r in puzzle:
        yield r[x]


print(solve(board))
