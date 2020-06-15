## 정리

##### heapq

```c++
#include<cstdio>
#include<vector>
using namespace std;
vector<int> heap;
void push_heap(vector<int>& heap, int newValue){
	heap.push_back(newValue);
	int idx = heap.size() - 1;
	while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]){
		swap(heap[idx], heap[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}
void pop_heap(vector<int>& heap){
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;
	while (1){
		int left = here * 2 + 1, right = here * 2 + 2;
		if (left >= heap.size()) break;
		int next = here;
		if (heap[next] < heap[left]) next = left;
		if (right < heap.size() && heap[next] < heap[right]) next = right;
		if (next == here) break;
		swap(heap[here], heap[next]);
		here = next;
	}
}
```

##### 변화하는 중간값 731p

https://www.algospot.com/judge/problem/read/RUNNINGMEDIAN

```c++
//트립 활용
#include<cstdio>
#include<algorithm>
using namespace std;
int n, a, b;
typedef int KeyType;
struct Node{
	KeyType key;
	int priority, size;
	Node *left, *right;
	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL){}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize(){
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};
typedef pair<Node*, Node*> NodePair;
//새로운 원소 추가하기 위해 split()필요함
NodePair split(Node* root, KeyType key){
	if (root == NULL) return NodePair(NULL, NULL);
	//루트가 key 미만이면 오른쪽 서브트리 쪼갬
	if (root->key < key){
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);	//오른쪽 서브트리에 쪼갠 왼쪽 서브트리(key보다 작은애들) 붙임
		return NodePair(root, rs.second);	//왼쪽 루트 달고, 오른쪽 쪼갠 오른쪽 서브트리(key보다 큰 애들) 붙임
	}
	//else
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}
Node* insert(Node* root, Node* node){
	if (root == NULL) return node;
	//node가 루트 대체
	if (root->priority < node->priority){
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	//루트보다 우선수위 낮으면 그냥 삽입
	else if (node->key < root->key){				//key 작으면 왼쪽
		root->setLeft(insert(root->left, node));
	}
	else{											//key 크면 오른쪽
		root->setRight(insert(root->right, node));
	}
	return root;
}
//원소 삭제하기 위해 merge() 필요함
Node* merge(Node* a, Node* b){
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority){
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}
Node* erase(Node* root, KeyType key){
	if (root == NULL) return root;
	//root 지우고 양 서브트리 합친 뒤 반환
	if (root->key == key){
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}
Node* kth(Node* root, int k){
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;	//root랑 같은경우
	return kth(root->right, k - leftSize - 1);	//k > l+1
}
struct RNG{
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983){}
	int next(){
		int ret = seed;
		seed = ((seed* (long long)a) + b) % 20090711;
		return ret;
	}
};
int runningMedian(int n, RNG rng){
	Node* root = NULL;
	int ret = 0;
	for (int cnt = 1; cnt <= n; cnt++){
		root = insert(root, new Node(rng.next()));
		int median = kth(root, (cnt + 1) / 2)->key;
		ret = (ret + median) % 20090711;
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while (tc--){
		scanf("%d %d %d", &n, &a, &b);
		printf("%d\n", runningMedian(n, RNG(a,b)));
	}
	return 0;
}

//heapq 활용
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
int n, a, b; 
struct RNG{
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983){}
	int next(){
		int ret = seed;
		seed = ((seed* (long long)a) + b) % 20090711;
		return ret;
	}
};
int runningMedian(int n, RNG rng){
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	for (int cnt = 1; cnt <= n; cnt++){
		if (maxHeap.size() == minHeap.size()){
			maxHeap.push(rng.next());
		}
		else{
			minHeap.push(rng.next());
		}
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()){
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}
int main(){
	int tc;
	scanf("%d", &tc);
	while (tc--){
		scanf("%d %d %d", &n, &a, &b);
		printf("%d\n", runningMedian(n, RNG(a, b)));
	}
	return 0;
}
```

