#min heap
def heapify(li, idx, n):
    l = idx * 2
    r = idx * 2 + 1
    s_idx = idx
    if(l <= n and li[s_idx] > li[l]):
        s_idx = l
    if (r <= n and li[s_idx] > li[r]):
        s_idx = r
    if s_idx != idx:
        li[idx], li[s_idx] = li[s_idx], li[idx]
        return heapify(li, s_idx, n)
def heap_sort(li):
    n = len(li)
    li = [0]+li
    #min heap 생성
    for i in range(n, 0, -1):
        heapify(li, i, n)

    #root 하나씩 제거하며 정렬
    for i in range(n, 0, -1):
        res.append(li[1])
        li[i], li[1] = li[1], li[i]
        heapify(li, 1, i-1)
