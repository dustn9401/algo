

import random
import sys
sys.setrecursionlimit(1000000)

n,m=30000,300000
f = open('C:\\input2927.txt', 'w')
f.write('%d\n' % (n))
for i in range(n):
    f.write('%d '%(random.randint(0,1000)))
f.write('\n')
f.write('%d\n'%(m))

str=['pen','bri','exc']
for i in range(m):
    a = random.randint(0,2)
    s = e = 0
    if a==0:
        s,e=random.randint(1,n),random.randint(0,1000)
    else:
        s,e=random.randint(1,n),random.randint(1,n)

    data = '%s %d %d\n' % (str[a], s, e)
    f.write(data)
f.close()