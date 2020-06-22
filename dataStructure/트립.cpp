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
//���ο� ���� �߰��ϱ� ���� split()�ʿ���
NodePair split(Node* root, KeyType key){
	if (root == NULL) return NodePair(NULL, NULL);
	//��Ʈ�� key �̸��̸� ������ ����Ʈ�� �ɰ�
	if (root->key < key){
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);	//������ ����Ʈ���� �ɰ� ���� ����Ʈ��(key���� �����ֵ�) ����
		return NodePair(root, rs.second);	//���� ��Ʈ �ް�, ������ �ɰ� ������ ����Ʈ��(key���� ū �ֵ�) ����
	}
	//else
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}
Node* insert(Node* root, Node* node){
	if (root == NULL) return node;
	//node�� ��Ʈ ��ü
	if (root->priority < node->priority){
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	//��Ʈ���� �켱���� ������ �׳� ����
	else if (node->key < root->key){				//key ������ ����
		root->setLeft(insert(root->left, node));	
	}
	else{											//key ũ�� ������
		root->setRight(insert(root->right, node));
	}
	return root;
}
//���� �����ϱ� ���� merge() �ʿ���
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
	//root ����� �� ����Ʈ�� ��ģ �� ��ȯ
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
