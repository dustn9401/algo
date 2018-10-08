import random
import sys
sys.setrecursionlimit(1000000)

def make_tree(node, lev):
    global n, count, tree, max_lev
    if lev > max_lev:
        return
    if  n <= count:
        return
    numchld = random.randrange(1, 10)

    for i in range(numchld):
        count+=1
        tree[node].append(count)
        if count==n:
            return
    for i in tree[node]:
        make_tree(i, lev+1)

n, m = 100000, 100000
count=1
max_lev = 10
tree = [[] for i in range(n+1)]
make_tree(1, 1)
print(tree)
weight=1
f=open('C:\\input.txt', 'w')
f.write('%d\n'%(n))
for i in range(1, len(tree)):
    for j in range(len(tree[i])):
        data="%d %d %d\n"%(i, tree[i][j], weight)
        f.write(data)
        weight+=1

f.write('%d\n'%(m))
for i in range(m):
    data='%d %d %d\n'%(random.randrange(1,3), random.randrange(1, n), random.randrange(1, n+1))
    f.write(data)
f.close()