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

##### 요새 689p

https://www.algospot.com/judge/problem/read/FORTRESS

```c++
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct TreeNode {
	vector<TreeNode*> children;
};
const int SIZE = 100;
int n, y[SIZE], x[SIZE], radius[SIZE];
int sqr(int x){ return x*x; }
int sqrdist(int a, int b){ return sqr(y[a] - y[b]) + sqr(x[a] - x[b]); }
bool encloses(int a, int b){ return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]); }
bool isChild(int parent, int child){
	if (!encloses(parent, child)) return false;
	for (int i = 0; i < n; i++)
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	return true;
}
//지금 까지 찾은 가장 긴 leaf-leaf 경로 저장
int longest;
int height(TreeNode* root){
	vector<int> heights;
	//각 자식을 루트로 하는 서브트리의 높이 계산
	for (int i = 0; i < root->children.size(); i++){
		heights.push_back(height(root->children[i]));
	}
	//자식 없으면 0 반환
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	//트리의 높이는 서브트리 높이 최대치에 +1
	return heights.back() + 1;
}
int solve(TreeNode* root){
	longest = 0;
	//트리의 높이와 최대 leaf-leaf경로 중 가장 큰 값 선택
	int h = height(root);
	return max(longest, h);
}
TreeNode* getTree(int root){
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ch++)
		if (isChild(root, ch))
			ret->children.push_back(getTree(ch));
	return ret;
}
int main(void) {
	int cases;
	cin >> cases;
	while (cases--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> x[i] >> y[i] >> radius[i];
		TreeNode* root = getTree(0);
		cout << solve(root) << endl;

	}
	return 0;
}

```

