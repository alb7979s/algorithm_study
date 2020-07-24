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