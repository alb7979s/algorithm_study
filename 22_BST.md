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

