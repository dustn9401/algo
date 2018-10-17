import random

f = open('C:/input1202.txt', 'w')
n,k = 300000, 300000
f.write('%d %d\n'%(n,k))

for i in range(n):
    m, v = random.randint(0, 1000000), random.randint(0,1000000)
    f.write('%d %d\n'%(m, v))
for i in range(k):
    c = random.randint(1, 1000000)
    f.write('%d\n'%(c))

f.close()
