class UnionFind:
    def __init__(self, n):
        self.parent = [i for i in range(n+1)]
    def find(self, u):
        if self.parent[u] == u: return u
        self.parent[u] = self.find(self.parent[u])
        return self.parent[u]
    def union(self, u, v):
        u = self.find(u)
        v = self.find(v)
        self.parent[u] = v
