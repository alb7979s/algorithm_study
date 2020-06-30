#플로이드
#모든 정점 출발, 모든 정점 도착 최단경로
#3중 for문으로 ij = min(ij, ikj)    바로 가는거, 경유해서 가는거 비교
#11404
from sys import*
setrecursionlimit(10**6)
input = stdin.readline
n=int(input())
m=int(input())
INF = 1e18
adj=[[]for _ in range(n)]
dist = [[INF]*n for _ in range(n)]
for i in range(m):
    a,b,c=map(int,input().split())
    a-=1;b-=1
    dist[a][b]=min(dist[a][b],c)
for i in range(n):
    dist[i][i]=0
for k in range(n):
    for i in range(n):
        for j in range(n):
            dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])
for i in range(n):
    for j in range(n):
        if dist[i][j]==INF: print(0, end=' ')
        else: print(dist[i][j],end=' ')
    print()
    
