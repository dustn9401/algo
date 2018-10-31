import sys
sys.setrecursionlimit(1000000)
input=sys.stdin.readline
n = int(input())
adj=[[] for i in range(n+1)]
chld=[[] for i in range(n+1)]
segs=[0]*(n+1)
idx=[0]*(n+1)
st=[1]*(n+1)
par=[1]*(n+1)
hv=[0]*(n+1)
w=[0]*(n+1)
eg_to_vt=[0]*(n+1)
node_w=[0]*(n+1)
tree=[0]*(n*4)
sz=1
for i in range(1, n):
    a,b,w[i]=map(int, input().split())
    adj[a].append([b, i]); adj[b].append([a, i])
def calc(c, b):
    global par, hv, w, cnt, chld
    for i in adj[c]:
        if i[0]^b: 
            chld[c].append(i[0])
            calc(i[0], c)
            hv[c]+=hv[i[0]]
            eg_to_vt[i[1]]=i[0]
            node_w[i[0]]=w[i[1]]
    par[c]=b; hv[c]+=1
def HLD(c, b):
    global segs, idx, sz, st
    hi = 0
    if chld[c]: hi = max(chld[c], key = lambda x: hv[x])
    for i in chld[c]:
        if i^hi: st[i]=i;HLD(i, c)
    if hi: st[hi]=st[c];HLD(hi, c)
    segs[sz]=c; idx[c]=sz; sz+=1
def init(s, e, i):
    global tree
    if s==e: tree[i] = node_w[segs[s]]; return tree[i]
    tree[i] = max(init(s, (s+e)//2, i*2), init((s+e)//2+1, e, i*2+1))
    return tree[i]
def query(s,e,l,r,i):
    if e<l or s>r: return 0
    if s>=l and e<=r: return tree[i]
    return max(query(s, (s+e)//2, l, r, i*2), query((s+e)//2+1, e, l, r, i*2+1))
def update(s,e,i,t,d):
    global tree
    if e<t or s>t: return tree[i]
    if s==e: tree[i] = d; return tree[i]
    tree[i] = max(update(s, (s+e)//2, i*2, t, d), update((s+e)//2+1, e, i*2+1, t, d))
    return tree[i]
def query2(s, e):
    ret = 0
    while st[s]^st[e]:
        if hv[st[s]]>hv[st[e]]: s,e=e,s
        ret = max(ret, query(1, n, idx[s], idx[st[s]], 1))
        s = par[st[s]]
    if hv[s]>hv[e]: s,e=e,s
    ret = max(ret, query(1, n, idx[s], idx[e] - 1, 1))
    return ret

calc(1,1)
HLD(1,1)
init(1,n,1)

m = int(input())
for i in range(m):
    a,b,c=map(int, input().split())
    if a==1: 
        update(1,n,1,idx[eg_to_vt[b]],c)
    else:
        print(query2(b,c))