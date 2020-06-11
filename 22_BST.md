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
NodePair split(Node* root, KeyType key){
	if (root == NULL) return NodePair(NULL, NULL);
	//root가 key 미만이면 오른쪽 서브트리 쪼갬
	if (root->key < key){
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//root가 key 이상이면 왼쪽 쪼갬
	NodePair ls = split(root->left, key);
	root->setLeft(ls.first);
	return NodePair(root, ls.second);
}
Node* insert(Node* root, Node* node){
	if (root == NULL) return node;
	//node가 루트 대체해야함. 해당 서브트리를 반으로 잘라 각각 자손으로
	if (root->priority < node->priority){
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}
```

