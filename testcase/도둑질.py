import random

f = open('C:\\inputTheif.txt', 'w')
n = 1000000
for i in range(n):
    f.write('%d '%(random.randrange(0,1000)))
f.close()