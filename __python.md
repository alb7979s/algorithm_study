#### -반올림

```python
#소수점 첫째자리 반올림
n=1.31231
print("%.0f" %n) 
```



#### 인스턴스, 메소드

ex) 3 + 5 실행하면

3, 5인 인스턴스를 \_\_add\_\_인 메소드 실행하여 계산

ex2) str() 함수를 호출하면, 인스턴스의 \_\_str\_\_메소드를 호출하는 구조



#### \_\_str\_\_ 문자열화해서 반환

```python
class test:
    def __init__(self):
        self.string = 'clzls'
    def __str__(self):
        return self.string
t = test()
print(t) 		#'clzls'출력
```



cf) \_\_repr\_\_ 도 문자열 반환하는거로 비슷한데, 이 친구는 객체를 평문으로 표현 하는 것



#### pypy제출시 setrecursionlimit() 하면 메모리 초과뜸

https://www.acmicpc.net/source/21346757

setrecursionlimit()없애니까 통과뜸.. 



#### 조합 / 순열 외장 함수

```python
from itertools import*
a=[1,2,3]
#순열, n개의 원소 r개 순서 있이 나열
perm = permutaions(a, 2)	#3P2 => [(1,2),(1,3),(2,1),(2,3),(3,1),(3,2)]
#조합, n개의 원소 r개 순서 없이 나열
comb = combinations(a, 2)	#3C2 => [(1,2),(1,3),(2,3)]
```

