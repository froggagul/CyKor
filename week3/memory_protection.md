## 1. canaries
* stack이 overflow되지 않게 랜덤의 값을 넣어서 변환되는지 확인한다.
* overflow가 발생하면 canary값이 손상되어 오버플로에 대한 경고를 출력, 손상된 데이터를 무효화처리한다.
### Typeof Canaries
1. random canaries
* canary의 값을 랜덤하게 생성한다.
* 생성하는 카나리의 값을 전역변수에 저장하는데, 이때 저장되는 주소는 읽을 수 없다(segmentation fault 발생)
    * 다만 canary의 값이 저장된 stack address, 혹은 스택의 값을 읽어올 수 있다면 canary의 값을 확인할 수 있다.


### off canary
```bash
gcc -fno-stack-protector 
```

### off NX
```bash
gcc -z execstack
```

2. ASLR
* stack start address가 실행시마다 바뀐다.
3. PI
* code 영역의 주소를 랜덤화한다.
4. DEP
* stack 영역에서 코드의 실행을 방지한다.
5. RELRO
* GOT 영역을 덮어쓸 수 없다.

gdb 명령어
* `checksec`
    * 보호기법 옵션 확인할 수 있음
* `vmmap`
    * 맵핑된 메모리를 확인할 수 있다.

관련 api
`mprotect`