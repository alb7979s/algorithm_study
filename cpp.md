#### atoi(const char* str) <cstdlib>

문자열 받아서 int타입으로 변환하여 리턴

#### c_str() <cstring>

해당하는 string의 첫번째 문자의 주소값 반환

```c++
//atoi
char* cStr = "20200515";
int num = atoi(cStr);
printf("%d", num); //20200515출력
//c_str
string cppstr = "CPPstring";
const char* cStr = cppstr.c_str();
printf("%s", cStr);
//"CPPstring" 출력 됨


```

#### operator()

연산자 오버로딩:: 매개변수 개수, 타입 다른 매개변수 지만 같은 연산하는 함수 하나로 쓰는거

```c++
//(리턴 타입) operator(연산자) (연산자가 받는 인자)
/* 팁
하지만 놀랍게도 C++ 에서는 사용자 정의 연산자를 사용할 수 있습니다. 어떠한 연산자들이 가능하나면, :: (범위 지정), . (멤버 지정), .* (멤버 포인터로 멤버 지정) 을 제외한 여러분이 상상하는 모든 연산자를 사용할 수 있다는 것입니다. 대표적으로
+, -, * 와 같은 산술 연산자
+=, -= 와 같은 축약형 연산자
>=, == 와 같은 비교 연산자
&&, || 와 같은 논리 연산자
-> 나 * 와 같은 멤버 선택 연산자 (여기서 * 는 역참조 연산자 입니다. 포인터에서 *p 할 때 처럼)
++, -- 증감 연산자
[] (배열 연산자) 와 심지어 () 까지 (함수 호출 연산자)
까지 모두 여러분이 직접 만들 수 있습니다.
*/

```

#### 문자열 길이

```c++
//scanf로 입력 받았을때
#include<cstring>
char str[100];
scanf("%s", str);
printf("%d",strlen(str));
//cin으로 입력
string str;
cin >> str;
cout << str.size();
```

