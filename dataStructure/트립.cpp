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
