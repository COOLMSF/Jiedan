cmd_/root/test/hello.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /root/test/hello.ko /root/test/hello.o /root/test/hello.mod.o ;  true
