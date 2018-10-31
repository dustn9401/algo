t = int(input())
while t:
    t -= 1
    n, k = map(int, input().split())
    d = list(map(int, input().split()))
    adj = [[] for i in range(n)]
    for i in range(k):
        x, y = map(int, input().split())
        adj[y-1].append(x-1)
    w = int(input())
    note = [[-1]*(n) for i in range(n)]
    v = [False]*(n)
    def dfs(idx, bef):
        if note[idx][bef] != -1: return note[idx][bef]
        if not len(adj[idx]): return d[idx]
        for i in adj[idx]:
            note[idx][bef] = max(note[idx][bef], d[idx] + dfs(i, idx))
        return note[idx][bef]
    print(dfs(w-1, 0))