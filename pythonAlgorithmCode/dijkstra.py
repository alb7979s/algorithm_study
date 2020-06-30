#1753
#한 정점에서 출발, 다른 모든 정점으로 가는 최단경로
#음의 간선 고려 안함
from heapq import*
from sys import*
input=stdin.readline
INF = 1e9
def dijkstra(V, E, start):
    dist = [INF for _ in range(V+1)]
    dist[start]=0
    pq=[]
    heappush(pq,(0, start))
    while pq:
        d, u = heappop(pq)
        if dist[u] != d: continue  # visit 따로 안만들고 방문확인
        for c, v in adj[u]:
            if d + c < dist[v]:
                dist[v] = d + c
                heappush(pq, (d+c, v))
    for i in range(1, V + 1):
        print(dist[i] if dist[i]!=INF else 'INF')
V, E = map(int,input().split())
start=int(input())
adj=[[]for _ in range(V+1)]
for i in range(E):
    a,b,c=map(int,input().split())
    adj[a].append((c, b))
dijkstra(V, E, start)
