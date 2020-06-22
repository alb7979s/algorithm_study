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
		rangeMin.resize(n * 4);	// 2**x >= n 의 x값 구한 뒤 n * (1 << (x+1))가 더 낫긴한데 4n으로 해도 딱히..
		init(array, 0, n - 1, 1);	
	}
	int init(const vector<int>& array, int left, int right, int node){
		if (left == right) return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int query(int left, int right, int node, int nodeLeft, int nodeRight){ //left, right :: 최소치 찾는 구간, nodeLeft, nodeRight :: 노드가 표현하는 범위
		//left..right 를 A로 놓고, nodeLeft..nodeRight를 B로 놓았을때,
		//(A ^ B) == 0(공집합) 이면 반환값 존재 x 따라서 return INF
		//(A ^ B) == A 이면 return rangeMin[node]
		//그 외 두 자손 query() 재귀호출 한 뒤 작은 값 반환
		if (right < nodeLeft || nodeRight < left) return INF; //겹치는 곳 없음
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];	//node가 표현하는 범위가 left..right에 완전 포함되는 경우
		int mid = (left + right) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	int query(int left, int right){	//query()를 외부에서 호출하기 위한 인터페이스래
		return query(left, right, 1, 0, n - 1);
	}
	//구간 트리의 갱신
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
		//표한하는 구간과 상관 없으면 무시
		if (index < nodeLeft || nodeRight < index)	return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue){ return update(index, newValue, 1, 0, n - 1); }
};
