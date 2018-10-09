import random
import sys
sys.setrecursionlimit(1000000)

def LCA(a,b):
    global level, parent
    if level[a] < level[b]:
        a,b=b,a
    while level[a] != level[b]:
        i = -1
        while level[parent[a][i + 1]] >= level[b]:
            i+=1
        a = parent[a][i]
    while a != b:
        i = 0
        while parent[a][i + 1] != parent[b][i + 1]:
            i+=1
        a, b = parent[a][i], parent[b][i]
    return a

def make_tree(node):
    global n, count, tree, max_lev, level, parent
    if count == n:
        return
    if level[node] >= max_lev:
        return
    numchld = random.randint(1, 10)

    for i in range(numchld):
        count+=1
        tree[node].append(count)
        parent[count][0] = node
        level[count] = level[node]+1
        if count>=n: return
    for i in tree[node]:
        make_tree(i)

n, m = 100000, 100000
parent = [[0 for j in range(20)] for i in range(n + 1)]
level = [1 for i in range(n+1)]
count = 1
max_lev = 50
tree = [[] for i in range(n + 1)]
make_tree(1)
for j in range(1, 20):
	for i in range(1, n + 1):
		parent[i][j] = parent[parent[i][j - 1]][j - 1]

f = open('input.txt', 'w')
f.write('%d %d\n' % (n, m))
for i in range(n):
    f.write('%d '%(random.randint(-2147483647, 2147483647)))
f.write('\n')
for i in range(1, len(tree)):
    for j in range(len(tree[i])):
        data = "%d %d\n" % (i, tree[i][j])
        f.write(data)

for i in range(m):
    print(i)
    s, e = random.randint(1,n), random.randint(1,n)
    lca = LCA(s,e)
    #num = level[s] - level[lca] + level[e] - level[lca] + 1
    #print('s=%d e=%d levs=%d leve=%d lca=%d lev[lca]=%d\n'%(s,e,level[s],level[e], lca, level[lca]))
    #num = random.randint(1, num)
    data = '%d %d %d\n' % (s, e, 1)
    f.write(data)
f.close()