## 정리

##### RMQ(Range Minimum Tree)

```c++
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF = (int)1e9;
struct RMQ {
	int n;
	//각 구간의 최소치
	vector<int> rangeMin;		
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || left > nodeRight) return INF;
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);		//query(0, n-1); 하면 루트부터 츄르륵 훑음
	}
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || index>nodeRight) return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};


```

##### 정렬된 수열의 특정 구간에서 최대 출현 빈도 계산 744p

```c++
struct RangeResult {
	int size;
	//가장 자주 등장하는 숫자의 출현 횟수
	int mostFrequent;
	//왼쪽 끝 숫자와 왼쪽 끝 숫자의 출현 횟수
	int leftNumber, leftFreq;
	//오른쪽
	int rightNumber, rightFreq;
};
RangeResult merge(const RangeResult& a, const RangeResult& b) {
	RangeResult ret;
	ret.size = a.size + b.size;
	ret.leftNumber = a.leftNumber;
	ret.leftFreq = a.leftFreq;
	if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
		ret.leftFreq += b.leftFreq;
	ret.rightNumber = b.rightNumber;
	ret.rightFreq = b.rightFreq;
	if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
		ret.rightFreq += a.rightFreq;
	ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
	if (a.rightNumber == b.leftNumber)
		ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);
	return ret;
}
```

