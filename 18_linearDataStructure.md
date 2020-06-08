## 정리



#### 동적 배열(C++에선 STL_vector 쓰면 됨)

```c++
//동적 배열 재할당 
if(size == capacity){
	int newCapacity = capacity + M;
	int* newArray = new int(newCapacity);
	for(int i=0; i<size; i++)
		newArray[i] = array[i];
	if(array) delete[] array;
	array = newArray;
	capacity = newCapacity;
}
array[size++] = newValue;
//m값을 두배씩 늘려주면 할당 평균적으로 O(1)나옴
```



#### 연결 리스트(C++ STL_list)

```c++
struct ListNode{
    int element;
    ListNode *prev, *next;	//이전 노드, 다음 노드 포인터
}
//삭제했던 원소 되돌리기(undo)
//삭제
void delete(ListNode* node){
	node -> prev -> next = node -> next;
	node -> next -> prev = node -> prev;
}
//복구
void recoverNode(ListNode* node){
    node -> prev -> next = node;
    node -> next -> prev = node;
}
```

---

##### 조세푸스 문제 620p

https://www.algospot.com/judge/problem/read/JOSEPHUS

```c++
#include<cstdio>
#include<list>
using namespace std;

void jose(int n, int k){
	list<int> survivors;
	for(int i=1; i<=n; i++) survivors.push_back(i);
	list<int>::iterator kill = survivors.begin();
	while(n > 2){
		kill = survivors.erase(kill); // earase() 지운 원소의 다음 원소 반환
		if(kill == survivors.end()) kill = survivors.begin();
		n--;
		for(int i=0; i<k-1; i++){
			kill++;
			if(kill == survivors.end()) kill = survivors.begin();
		}
	}
	printf("%d %d\n", survivors.front(), survivors.back());
}

int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		int n, k;
		scanf("%d %d", &n, &k);
		jose(n, k);
	}
	return 0;
}
```

