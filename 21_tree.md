## 정리



```c++
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
//트리 순회하며 출력
void printLabels(TreeNode* root){
	cout << root->label << endl;
	for (int i = 0; i < root->children.size(); i++)
		printLabels(root->children[i]);
}
//높이 구하기
int height(TreeNode* root){
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + height(root->children[i]));
	return h;
}
```

##### 트리 순회 순서 변경 686p

https://www.algospot.com/judge/problem/read/TRAVERSAL

```c++
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

vector<int> slice(const vector<int>& v, int a, int b){
	return vector<int>(v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder){
	const int N = preorder.size();
	if (preorder.empty()) return;
	const int root = preorder[0];
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	const int R = N - 1 - L;
	//왼쪽 서브트리 출력
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	//오른쪽 서브트리 출력
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	//마지막으로 루트 출력
	cout << root << ' ';
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tc;
	cin >> tc;
	while (tc--){
		int n;
		cin >> n;
		vector<int> preorder, inorder;
		int t;
		for (int i = 0; i < n; i++){
			cin >> t;
			preorder.push_back(t);
		}
		for (int i = 0; i < n; i++){
			cin >> t;
			inorder.push_back(t);
		}
		printPostOrder(preorder, inorder);
		cout << endl;
	}
	return 0;
}
```

