import random
n,m = 100000, 5000
arr = [random.randint(-100000000, 100000000) for i in range(1, n+1)]
random.shuffle(arr)
f=open('C:\\input.txt', 'w')
f.write('%d %d\n'%(n, m))
for i in arr:
    f.write('%d '%(i))
f.write('\n')

#fout = open('C:\\output.txt', 'w')
cnt = 0
for i in range(m):
    a,b=random.randrange(1, n+1), random.randrange(1, n+1)
    if a > b:
        a,b=b,a
    c = random.randint(1,b-a+1)
    f.write('%d %d %d\n'%(a,b,c))
    #fout.write('%d\n'%(sorted(arr[a:b+1])[c-1]))
    cnt+=1
    print(cnt)
f.close()
#fout.close()

