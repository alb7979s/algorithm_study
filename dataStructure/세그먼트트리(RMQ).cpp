#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF = (int)1e9;
struct RMQ {
	int n;
	vector<int> rangeMin;
	RMQ(const vector<int>& array){
		n = array.size();
		rangeMin.resize(n * 4);	// 2**x >= n �� x�� ���� �� n * (1 << (x+1))�� �� �����ѵ� 4n���� �ص� ����..
		init(array, 0, n - 1, 1);	
	}
	int init(const vector<int>& array, int left, int right, int node){
		if (left == right) return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int query(int left, int right, int node, int nodeLeft, int nodeRight){ //left, right :: �ּ�ġ ã�� ����, nodeLeft, nodeRight :: ��尡 ǥ���ϴ� ����
		//left..right �� A�� ����, nodeLeft..nodeRight�� B�� ��������,
		//(A ^ B) == 0(������) �̸� ��ȯ�� ���� x ���� return INF
		//(A ^ B) == A �̸� return rangeMin[node]
		//�� �� �� �ڼ� query() ���ȣ�� �� �� ���� �� ��ȯ
		if (right < nodeLeft || nodeRight < left) return INF; //��ġ�� �� ����
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];	//node�� ǥ���ϴ� ������ left..right�� ���� ���ԵǴ� ���
		int mid = (left + right) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	int query(int left, int right){	//query()�� �ܺο��� ȣ���ϱ� ���� �������̽���
		return query(left, right, 1, 0, n - 1);
	}
	//���� Ʈ���� ����
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
		//ǥ���ϴ� ������ ��� ������ ����
		if (index < nodeLeft || nodeRight < index)	return rangeMin[node];
		//Ʈ���� �������� ������ ���
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()�� �ܺο��� ȣ���ϱ� ���� �������̽�
	int update(int index, int newValue){ return update(index, newValue, 1, 0, n - 1); }
};
