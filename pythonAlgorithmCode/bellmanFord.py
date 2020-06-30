#벨만포드
#최단경로는 사이클을 포함할 수 없기 때문에 최대 V-1개의 간선 사용
#매 라운드 모든 에지 점검 따라서 O(|V||E|), |E|는 최대 V**2
#11657
from sys import*
input=stdin.readline
n,m=map(int,input().split())
adj=[[]for _ in range(n)]
for i in range(m):
    a,b,c=map(int,input().split())
    a-=1;b-=1
    adj[a].append((b,c))
INF=1e9
dist=[INF]*n
cycle=False
dist[0]=0
for i in range(n):
    for u in range(n):
        for v,d in adj[u]:
            nd = dist[u]+d
            if dist[u] != INF and dist[v] > nd:
                dist[v] = nd
                if i == n-1: cycle=True
if cycle: print(-1)
else:
    for i in range(1, n):
        print(dist[i] if dist[i]!=INF else -1)
