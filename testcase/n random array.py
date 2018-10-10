import random
n,m = 100000, 5000
arr = []
num = 0
for i in range(n):
    print(i)
    while num in arr:
        num = random.randint(-1000000000, 1000000000);
    arr.append(num)
random.shuffle(arr)
f=open('input7469.txt', 'w')
f.write('%d %d\n'%(n, m))
for i in arr:
    f.write('%d '%(i))
f.write('\n')

cnt = 0
for i in range(m):
    a=random.randint(1, n)
    b=random.randint(a, n)
    c = random.randint(1,b-a+1)
    f.write('%d %d %d\n'%(a,b,c))
    cnt+=1
    print(cnt)
f.close()

