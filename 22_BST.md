## 정리



##### 너드인가, 너드가 아닌가?2 (702p)

https://www.algospot.com/judge/problem/read/NERD2

```c++
#include<cstdio>
#include<string>
#include<map>
using namespace std;

map<int, int> coords;
//새로운 점 x, y 가 기존의 다른 점들에 지배당하는지 확인
bool isDominated(int x, int y){
	//x보다 오른쪽 있는 점 중 가장 왼쪽 점 찾음
	map<int, int>::iterator it = coords.lower_bound(x);
	//그런 점이 없으면 지배당하지 않음
	if (it == coords.end()) return false;
	//이 점은 x보다 오른쪽에 있는 점 중 가장 위에 있는 점이므로, x,y가 어느 점에 지배 되려면 이 점에도 지배 되어야함
	return y < it->second;
}
void removeDominated(int x, int y){
	map<int, int>::iterator it = coords.lower_bound(x);
	//x, y 보다 왼쪽 점 없음
	if (it == coords.begin()) return;
	--it;
	while (true){
		//x, y 바로 왼쪽 오는 점, it가 표시하는 점이 x,y에 지배되지 않으면 종료
		if (it->second > y) break;
		//이전 점이 없으면 it만 지우고 종료
		if (it == coords.begin()){
			coords.erase(it);
			break;
		}
		//있으면 이전 점으로 이터레이터 옮기고 it 지움
		else{
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}
//새 점 x,y가 추가 되었을 때 coords 갱신하고, 다른 점에 지배당하지 않는 점들의 개수 반환
int registered(int x, int y){
	//x, y 이미 지배 당하는 경우 버림
	if (isDominated(x, y)) return coords.size();
	//기존에 있던 점 중 x, y에 지배당하는 점 지움
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}
int main(){
	int tc;
	scanf("%d", &tc);
	while (tc--){
		int n, sum = 0;
		coords.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			int p, q;
			scanf("%d %d", &p, &q);
			sum += registered(p, q);
		}
		printf("%d\n", sum);
	}
	return 0;
}
```

##### 트립

```c++
#include<cstdio>
#include<algorithm>
using namespace std;

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
```

##### 트리를 이용한 k번째 원소 찾기

```c++
Node* kth(Node* root, int k){
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;	//root랑 같은경우
	return kth(root->right, k - leftSize - 1);	//k > l+1
}
```

##### 트리를 이용한 x보다 작은 원소 세기

```c++
int countLessThan(Node* root, KeyType key){
	if (root == NULL) return 0;
	if (root->key >= key) return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}
```

##### 삽입 정렬 뒤집기 718p

https://www.algospot.com/judge/problem/read/INSERTION

```c++
#include<cstdio>
#include<algorithm>
using namespace std;

typedef int KeyType;
int n, shifted[50000];
int A[50000];

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
//트리 이용해서 k번째 원소 찾기
Node* kth(Node* root, int k){
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;	//root랑 같은경우
	return kth(root->right, k - leftSize - 1);	//k > l+1
}
//삽입 정렬 뒤집기
void solve(){
	Node* candidates = NULL;
	for (int i = 0; i < n; i++)
		candidates = insert(candidates, new Node(i + 1));
	for (int i = n - 1; i >= 0; --i){
		int larger = shifted[i];
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}
}
int main(){
	int tc;
	scanf("%d", &tc);
	while (tc--){
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &shifted[i]);
		solve();
		for (int i = 0; i < n; i++)
			printf("%d ", A[i]);
		printf("\n");
	}
}
```

