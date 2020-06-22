#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct TreeNode{
	string label;
	TreeNode* parent;
	vector<TreeNode*> children;
};
//Ʈ�� ��ȸ�ϸ� ���
void printLabels(TreeNode* root){
	cout << root->label << endl;
	for (int i = 0; i < root->children.size(); i++)
		printLabels(root->children[i]);
}
//���� ���ϱ�
int height(TreeNode* root){
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + height(root->children[i]));
	return h;
}
