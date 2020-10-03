# what_day_is_it
크게 함수는 세가지로 구성되어있다. `main()`, `foo()`, `bar()`
## 기본적인 부분들
### 함수 프롤로그
```asm
push    rbp
mov     rbp, rsp
```
RSP는 스택의 맨 꼭대기를 가리키고 있다. RBP를 스택에 저장하는 이유는 이전에 수행하던 함수이ㅡ 데이터를 보존하기 위해서이다. 이것을 base pointer라고도 부른다. 그래서 함수가 시작될 때에는 이러헥 stack pointer와 base pointer를 새로 지정하는데, 이러한 과정을 함수 프롤로그 과정이라고 한다.  
함수 프롤로그 과정 이후, 아래의 instruction들이 실행된다,
```
mov     rax, QWORD PTR fs:0x28
mov     QWORD PTR [rbp-0x8], rax
xor     eax, eax
```
* [스택을 보호하기 위해 하는 instruction라는데](https://stackoverflow.com/questions/10325713/why-does-this-memory-address-fs0x28-fs0x28-have-a-random-value#:~:text=So%20what%20you're%20seeing,performing%20a%20stack%2Dguard%20check.), 자세한 내용은 추후 알아볼 계획이다.

## main()
main 함수는 크게 네 파트로 구성되어있다. 
1. `mov QWORD PTR [rbp-0xn], 0x0`들의 모임
2. `call foo()`
3. `call bar()`
4. `puts()`와 `printf()`들의 모임
    * 해당 파트는 과제 특성상 분석하지 않았다.
1. `mov QWORD PTR [rbp-0xn], 0x0`
    * 확장된 스택의 크기가 0x70이고, rbp-0x70부터 rbp-0x10까지 0x0을 넣는 것으로 보아 배열을 선언하고 0x0 값을 할당하는 것을 알 수 있다.
    * 처음에는 QWORD만큼의 크기를 넣기에 배열이 long/long long 타입인 것으로 예상되었으나 이는 `*main+123`에 있는 `mov DWORD PTR[rbp-0x10],0x0`을 설명하지 못한다. int형 변수를 선언하고 long 타입 배열을 선언해도 아래와 같은 instruction은 나오지 않았다.
    * 이후 foo와 bar 함수를 분석하고 노가다를 통해 다음 c코드가 맞는 코드 임을 알아냈다.
    ```c++
    char buffer[100]={'\0',};
    ```
2. `call foo()`
    * foo를 호출하기 전, 인자에 해당하는 rdi와 rsi에 특정 변수들의 주소값을 넣는 것을 확인할 수 있다.
    * 하나는 `rbp-0x70`, 즉 앞의 `buffer[100]`의 주소이고
    * 나머지 하나는 `rip+0x2bdd`로 디버깅을 통해 문자열 `"Hello, world!"`임을 알아냈다.
    * 이후 foo의 return 값이 들어있는 eax 레지스터의 값이 1이면 함수를 종료 시킨다.
    ```asm
    call    0x11c9<foo>
    test    eax,eax #eax의 값이 0이 아닌 경우
    je      0x1450  #je instruction이 발동되지 않는다.
    mov     edi,0x0
    call    0x10d0<exit@plt> # 이후 exit(0)을 실행시킨다.
    ```
3. `call bar()`
    * 2번의 `call foo()`와 크게 다르지 않다.
    * 다만 이번에는 buffer의 주소만을 인자로 전달한다.
    * 2번과 마찬가지로 return값이 1이면 함수를 종료시킨다. 아닌 경우, printf와 puts 함수를 여러번 호출하는데, 여기서 flag를 전달함을 예측해볼 수 있다.
## foo()
앞의 main에서 return 값이 0이 아니면 exit을 하므로, 언제 0을 반환하고 언제 0이 아닌 값을 반환하는지를 중점적으로 보았다.
1. puts와 gets 함수 호출
* puts함수를 호출하고 gets 호출하는데 해당 인자는 각각 먼저 전달받은 `"Hello, world!"`의 주소와 `buffer[100]`의 주소이다.
* 입력받은 값이 buffer에 저장됨을 알 수 있다.
2. 반복문
* 일반 인자만을 전달할 경우, 스택의 확장이 0x10만큼만 이루어지는데 0x20만큼 이루어지는 것으로 보아 추가 인자가 있음을 알 수 있다.
* 또한 rbp-0x4 부분의 변수를 1씩 더하고, 비교하고, jmp를 통해 돌아가는 명령어가 반복되는 것으로 보아 해당 코드는 반복문임을 알 수 있다.
* 또한 반복문 내에서 rbp-0x20의 주소에서 i만큼 더하여 `test al, al`을 하는것으로 보아 `buffer[i]`가 0인지 검사하는 것을 알 수 있다.
```c++
int i;
for(i=0;i<100;i++) {
    if (buff[i]) continue;
}
```
3. return 값의 지정
* i가 100이면 1을 return,
* 다른 경우는 0을 return하고 있다.
* 결론적으로 i는 buffer의 길이를 제고 있었던 것이다.

## bar()
앞의 main에서 return 값이 0이 아니면 exit을 하므로, 언제 0을 반환하고 언제 0이 아닌 값을 반환하는지를 중점적으로 보았다.  
반복적으로 보이는 패턴은
1. `mov WORD PTR [rbp-0x18]`, `add rax, 0x1`, `movzx eax, BYTE PTR [rax]`, `movsx eax, al`
2. al로 xor, cmp 등의 연산을 실행
3. 조건을 만족하지 못하면 1을 return, 아니면 계속 진행
이다.  
이를 바탕으로 코드를 재구성했다.

## 결론
최종 예측한 코드는 다음과 같다.
```c++
#include<stdio.h>
#include<stdlib.h>

char h[20] = "Hello, world!\0";

int foo(char *str, char* buff) {
	int i;
	puts(str);
	scanf("%s", buff);
	for (i=0;i!=100;i++) {
		if (buff[i]) continue;
	}
	if (i == 100) return 1;
	return 0;
}
int bar(char* buff) {
	char temp[2]="\x23\x11";
	if(buff[0]^temp[0]==0x60) {
		if(buff[1]+buff[1]==0x90) {
			if(buff[2]*0x47==0x1793) {
				if(buff[3]+buff[1]==0xa2) {
					if(buff[4]-buff[3]==0x2a) {
						if(buff[5]^temp[1]==0x54) {
							if(buff[6]<<2==0xc0) {
								if (buff[7]>0x46) {
									if(buff[7]==0x47) {
										if(buff[8]==0x21) {
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}
int main() {
	char buffer[100] = {'\0',};
	if(foo(h, buffer)) {
		exit(0);
	} else {
		if(bar(buffer)) {
			printf("Nah...\n");
			exit(0);
		} else {
			printf("Correct!!\n");
			printf("cykor{h4ppy_CHU_5E0G!_4nd_plz_5tay_4t_h0m3!!}\n");
		}
	}
	return 0;
}
```

## 여담-answer
`CHU_5E0G!`을 입력하게 되면
`cykor{h4ppy_CHU_5E0G!_4nd_plz_5tay_4t_h0m3!!}` flag를 돌려준다,